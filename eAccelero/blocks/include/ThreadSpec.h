
////////////////////////////////////////////////////////////////////////////
/// @file ThreadSpec.h
///
/// Purpose: Utility for maintaining thread specific data.
///
////////////////////////////////////////////////////////////////////////////

#ifndef __EACC_THRSPEC_H__
#define __EACC_THRSPEC_H__

#include <pthread.h>
#include "Exception.h"
#include "Component.h"

namespace eAccelero
{

///////////////////////////////////////////////////////////////////////////////
/// \brief Utility class the simplifies the maintanence of thread specific
/// objects.
/// 
/// Situations might arise where once must want to maintain some objects 
/// accesible only on a per thread basis. This utility class is a wrapper 
/// around the pthread apis' for maintaining thread specific objects.
///
/// The usage of thread specific objects is always the same, irrespective of the
/// objects maintained.
///    - create a key for the thread specific objects globally
///    - If thread specific object is null create a new object and set the
///      object into a thread specific storage
///    - when the thread exists delete the thread specific object.
///
/// This class simplifies all these actions and provides an easy interface to
/// the user. User need not care about deleting the object when the thread
/// exists, neither should he write code for maintaining thread specific
/// objects.
///
/// This class object should be defined in either global, class static, file
/// static or function static scopes.
/// 
/// USAGE:
///    class DBAccess
///    {
///      public:
///        Context* fetch(int sessionId)
///        {
///            // Type cast operator does the get, null checks and 
///            // creates a new threadSpec obj if required
///            ContextIter* iter = tsContextIter;
///            return iter->lookup_rowSearch(sessionId);
///        }
///      private:
///        // Note: no pointer passed as the template arg
///        static ThreadSpec<ContextIter> tsContextIter;
///    }
///
///////////////////////////////////////////////////////////////////////////////
template<typename TSType>
class ThreadSpec
{
  public:
    /////////////////////////////////////////////////////////////////////////
    /// Function: ThreadSpec 
    ///
    /// Description: Constructor. As this object must be static, this
    /// constructor will be called before even main() starts. Creates a key for
    /// the thread specific object and installs a destructor, that will be
    /// lauched when a thread exits.
    /// 
    /// @return None. 
    ///
    /////////////////////////////////////////////////////////////////////////  
    ThreadSpec()
    {
        int ret;

        ret = pthread_key_create(&m_key, 
                    ThreadSpec<TSType>::Destructor);
        if (ret != 0)
        {
            throw SystemException("Thread Specific Key create failed", ret);
        }        

    }

    /////////////////////////////////////////////////////////////////////////
    /// Function: ~ThreadSpec 
    ///
    /// Description: Destructor, which deletes the thread specific key.
    /// 
    /// @return None. 
    ///
    /////////////////////////////////////////////////////////////////////////
    ~ThreadSpec()
    {
        int ret;

        ret = pthread_key_delete(m_key);
        if (ret != 0)
        {
            // Don't throw an exception in the destructor. In any case this will
            // be called only when the program is terminating.
            printf("Thread Specific Key delete failed: %d", ret);
        }    
    }

    /////////////////////////////////////////////////////////////////////////
    /// Function: GetData 
    ///
    /// Description: Returns a pointer to the thread specific object. This
    /// method should be called if a non-0default constructor for the object is
    /// to be called. Objects with default constructors should use the type
    /// casting operator instead.
    /// 
    /// USAGE:
    ///    Context* fetch(int sessionId)
    ///    {
    ///        ContextIter* iter = tsContextIter.GetData();
    ///        if (iter == NULL)
    ///        {
    ///            // Constructor to be used is non-default
    ///            iter = new ContextIter(arg1, arg2);
    ///            tsContextIter = iter; // Invokes the assignment operator
    ///        }
    ///    }
    ///
    /// @return Pointer to the thread specific object. 
    ///
    /// @see operator TSType*(), operator=()
    ///
    /////////////////////////////////////////////////////////////////////////
    TSType* 
    GetData()
    {
        return reinterpret_cast<TSType*>(pthread_getspecific(m_key));
    }

    /////////////////////////////////////////////////////////////////////////
    /// Function: operator TSType* 
    ///
    /// Description: Get the thread specific object. For the first call of this
    /// operator in a thread, the object will be NULL. Hence it creates a new
    /// object by invoking the default constructor. 
    ///
    /// If the user wants to invoke a non default constructor he must use the
    /// GetData() instead.
    /// 
    /// @return Pointer to the thread specific object. 
    ///
    /// @see operator=(), GetData()
    ///
    /////////////////////////////////////////////////////////////////////////
    operator TSType*()
    {
        TSType* data = reinterpret_cast<TSType*>(pthread_getspecific(m_key));
        if (data == NULL)
        {
            data = new TSType();
            // Set specific data. Uses the assignment operator
            *this = data;
        }

        return data;
    }

    // Same as above
    TSType* operator ->()
    {
        TSType* data = reinterpret_cast<TSType*>(pthread_getspecific(m_key));
        if (data == NULL)
        {
            data = new TSType();
            // Set specific data. Uses the assignment operator
            *this = data;
        }

        return data;        
    }

    /////////////////////////////////////////////////////////////////////////
    /// Function: operator= 
    ///
    /// Description: Sets the set specific data. Normally called within the
    /// operator TSType*(). Optionally used if the user wants to use a non
    /// default constructor for creating the object.
    /// 
    /// @param [in] data - Pointer to the object to be set as thread speicfic
    ///                    object.
    ///
    /// @return Reference to the ThreadSpec template class to support
    ///         cascading. 
    ///
    /// @see GetData(), operator TSType*()
    ///
    /////////////////////////////////////////////////////////////////////////
    ThreadSpec<TSType>& 
    operator=(TSType* data)
    {
        int ret;

        ret = pthread_setspecific(m_key, data);
        if (ret != 0)
        {
            throw SystemException("Set Specific data failed", ret);
        }        

        return *this;
    }

  protected:
    /////////////////////////////////////////////////////////////////////////
    /// Function: Destructor 
    ///
    /// Description: Will be invoked every time a thread exits and there is a
    /// thread specific object in that thread which is not NULL.
    /// 
    /// @param [in] data - Pointer to the thread specific object.
    ///
    /// @return None. 
    ///
    /// @see ThreadSpec()
    ///
    /////////////////////////////////////////////////////////////////////////  
    static void 
    Destructor(void* data)
    {
        // No need to check for NULL. If the data is NULL, this default
        // constructor would not have been called. (man pthread_key_create)
        delete reinterpret_cast<TSType*>(data);
    }

    pthread_key_t m_key;
};

} // namespace eAccelero

#endif // __EACC_THRSPEC_H__

