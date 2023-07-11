/*********************************-*-H-*-************************************
 *                                                                          *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************/
#ifndef __Rule_h__
#define __Rule_h__

#include <vector>
#include <map>
#include <unordered_map>
#include <stdint.h>
#include <string.h>

#include "ExprParser.h"
#include "Sync.h"

/**
 * @file Rules.h
 * Refer @ref rule_proc "Rules" for more information.
 */

/**@page rule_proc Rule Processor
 * 
 * @section rule_intro Rule:
 * 
 * A rule is a conditional expression, that will be executed in runtime, which
 * would yield a boolean result (true/false). The expressions are typically
 * formed by the message variables. These rules are used to assert if an 
 * incoming message fields matches the given conditions or not. It only provides
 * an assertion, not the action to be taken if the assertion is successful.
 * 
 * For example to check if an incoming diameter message contains the Origin-Host
 * value as 'somehost.com' and Application-Id as 'Gy', this can be expressed as
 * a rule expression of the form 
 * @code    
 *      "dia.Origin-host == 'somehost.com' and dia.Application-Id == 4"
 * @endcode
 * 
 * To know more on expressions, see eAccelero::Expr.
 * 
 * A rule is identified with a unique integer rule-id. If one or more rule matches,
 * the rule with the highest priority gets more precedence. Multiple rules form
 * a RuleTable. The variables in the rule table are not interpreted by the 
 * RuleTable themselves, rather a callback RuleTable::RegisterVarHandler() is 
 * provided to interpret the variables.This makes customization of the message
 * fields easier for various other protocols.
 * 
 * @section rule_atom RuleAtom:
 * 
 * A rule is composed of units known as a RuleAtom, which roughly translates to
 * a conditional expression. The RuleAtoms are constructed from the 
 * eAccelero::Expr. A pre order traversal of the expression tree, yields a 
 * postfix notation of the expression, which can evaluated in sequence to get the
 * result of the expression. For example, if the expression is of the form
 * @code
 *      (a >= b && b > c) || (e != d && b <= d)
 * @endcode
 * 
 * will be evaluated in the post fix RuleAtom form to
 * @code
 *   0 ->  a >= b           And-Fail-Jump: 2
 *   1 ->  b > c
 *   2 ->  [0] && [1]       Or-Success-Jump: 6
 *   3 ->  e != d
 *   4 ->  b <= d
 *   5 ->  [3] && [4]
 *   6 ->  [2] || [5] 
 * @endcode
 *
 * Each entry mentioned above is a rule atom. When the Rule is evaluated, each
 * RuleAtom is evaluated one by one and the result is stored in a runtime 
 * variable storage of the RuleAtom. Some rule atoms like (2), (5) or (6) depend
 * on the results of the previous RuleAtom results.Once all the RuleAtoms are
 * evaluated, the result of the final RuleAtom (here it is [6]), is the final
 * result. Each RuleAtom contains two Operands and the operation.
 * 
 * @subsection rule_atom_opt Rule optimization:
 * 
  * As a optimization, two jumps - And-Fail-Jump and Or-Sucess-Jump are added.
 * 
 * In the above example, if the RuleAtom [0] evaluates to false, then we don't
 * have to evaluate the RuleAtom [1] and the atom [2] will anyways be false.
 * So the And-Fail-Jump is set to jump to the RuleAtom [2]. Then the result of
 * [2] is set to false and the rest of the Atoms are evaluated one by one.
 * 
 * If the entire expression [2] (a >= b && b > c), evaluates to true, then we
 * don't have to evaluate the rest of the expression, because anyways the 
 * whole expression will evaluate to true. Hence the Or-Success-Jump is set to
 * [6]. Once [2] is true, the evaluation jumps to the [6] and sets it true.
 * 
 * @section rule_var_handle Variable Handling:
 * 
 * Variables are the message fields, whose value will be known only at runtime
 * when the expression is evaluated against an incoming message.
 
 * There are two aspects to the variable handling
 *  - Interpreting the variables at the rule configuration time
 *  - Evaluating the value of the variables at rule time
 * 
 * @subsection rule_var_interpret Variable Interpretation:
 * 
 * eAccelero::Rule is designed as a generic means of evaluating expressions to
 * yield a true/false result. Since each protocol will have its own set of 
 * messages, the message fields interpretation is moved out of the Rules. 
 * However the RuleTable provides a registration method to regiser callbacks to
 * handle any protocol message. Once the protocol specific VarHandler undestand
 * the fields, it returns the RuleTable with a sequence of integers known as 
 * VarIdentifier. The rule processor does not interpret this VarIdentifier
 * directly, rather the same VarIdentifier is passed to the Accessor method of
 * the protocol during evaluating the expression.
 * 
 * When returning the VarIdentifier, the protocol handler also provides the 
 * Accessor method to the rule processor. This accessor method knows how to get
 * the value of the message variable, given the VarIdentifier for it.
 * 
 * @subsection rule_var_eval Variable Evaluation:
 * 
 * When the RuleAtom is being evaluated, the rule processor knows the 
 * VarIdentifier of the variable and using the accessor method provided in the
 * interpretation step, the value of the variable is obtained. Then the 
 * appropriate operation (logical/relation) is performed on the Operand values.
 * 
 */

namespace eAccelero
{

EACC_DEFINE_EXCEPTION_CLASS(RuleException, Exception, "Rule Exception")
#define RuleExceptionLog(...) GEN_EXCEPTION_LOG(eAccelero::RuleException, ##__VA_ARGS__)

/**
 * @class OperandValBase
 * @brief Is an abstraction for the operand value.
 * 
 * This is an abstract class providing Comparison and logical operation hooks.
 * The concrete class should implement these operations.
 */
class OperandValBase
{
 public:
    virtual ~OperandValBase() {}
    virtual bool Greater(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
    virtual bool GreaterEqual(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
    virtual bool Lesser(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
    virtual bool LesserEqual(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
    virtual bool EqualTo(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
    virtual bool NotEqual(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
    virtual bool And(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
    virtual bool Or(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
    // pattern matching
    virtual bool Match(OperandValBase& rhs)
    {
        throw RuntimeException("Op not implemented");
    }
};

typedef bool (OperandValBase::*OpFunctor)(OperandValBase& rhs);

/**
 * @class OpFunctorAccess
 * @brief This is an encapsulation over the Function pointer table for opeartions
 * 
 * To carry out an operation like >=, && etc..., the actual implementation
 * function pointers are stored in the m_fptrTable. This table is hardcoded and 
 * cannot be changed at runtime.
 */
class OpFunctorAccess
{ 
 public:
    /**
     * @brief Given the operation, returns the function pointer to evaluate it
     * @param op    Operator code
     * @return Returns the requested function pointer
     */
    static OpFunctor Get(int op) 
    { 
        return m_fptrTable[op];
    }
 protected:
    /** Table holding the function pointers to carry out the conditional
     *  operation
     */
    static OpFunctor m_fptrTable[Lexer::TOK_MAX];
};

/**
 * @class OperandVal<T>
 * @brief Generic operand value class, implementing the basic operations
 * 
 * T value can be the plain old data types (POD) or any class that supports
 * the relational operations. This generic class however doesn't implement the
 * And and Or operations. That are required only by the RuleAtom, whose value
 * will be of type IntVal.
 */
template <typename T>
class OperandVal: public OperandValBase
{
 public:
    /**
     * @brief Default constructor. 
     */
    OperandVal()
    {
    }
    
    /**
     * @brief Constuctor constructed from the value data type
     * @param val   Value of the data type
     */
    OperandVal(const T& val)
        : m_val(val)
    {
    }

    /**
     * @brief Checks if the object's value is greater than value of rhs
     * @param rhs   the object of comparison
     * @return If greater returns true else false
     */
    virtual bool Greater(OperandValBase& rhs)
    {
        return m_val > static_cast<OperandVal&>(rhs).m_val;
    }
    
    /**
     * @brief Checks if the object's value is greater than or equal to rhs
     * @param rhs   the object of comparison
     * @return If greater than or equal to then returns true else false
     */
    virtual bool GreaterEqual(OperandValBase& rhs)
    {
        return m_val >= static_cast<OperandVal&>(rhs).m_val;
    }
    
    /**
     * @brief Checks if the object's value is lesser than value of rhs
     * @param rhs   the object of comparison
     * @return If lesser returns true else false
     */
    virtual bool Lesser(OperandValBase& rhs)
    {
        return m_val < static_cast<OperandVal&>(rhs).m_val;
    }
    
    /**
     * @brief Checks if the object's value is lesser than or equal to rhs
     * @param rhs   the object of comparison
     * @return If lesser than or equal to then returns true else false
     */
    virtual bool LesserEqual(OperandValBase& rhs)
    {
        return m_val <= static_cast<OperandVal&>(rhs).m_val;
    }
    
    /**
     * @brief Checks if the object's value is equal to the rhs value
     * @param rhs   the object of comparison
     * @return Checks if the object's value is equal to the rhs value
     */
    virtual bool EqualTo(OperandValBase& rhs)
    {
        return m_val == static_cast<OperandVal&>(rhs).m_val;
    }
    /**
     * @brief Checks if the object's value is not equal to the rhs value
     * @param rhs
     * @return Checks if the object's value is not equal to the rhs value
     */
    virtual bool NotEqual(OperandValBase& rhs)
    {
        return m_val != static_cast<OperandVal&>(rhs).m_val;
    }

    /**
     * @brief Set the value for this object
     * @param val   Value of the object
     */
    void Set(T &val)
    {
        m_val = val;
    }
    
    /**
     * @brief Get the value of this object
     * @return Value of the object
     */
    T& Get()
    {
        return m_val;
    }

 protected:
    T m_val;    /**< Value of the object */
};

/**
 * @class IntVal
 * @brief Specialized Integer value object
 *  
 * Used specifically by the RuleAtom object, and hence the And and Or operations
 * are overridden and implemented. 
 */
class IntVal: public OperandVal<int>
{
 public:
    /**
     * @brief Default constructor
     */
    IntVal()
        : OperandVal<int>((int)0)
    {
    }
    
    /**
     * @brief Constructor accepting an integer value
     * @param val   integer value
     */
    IntVal(const int& val)
        : OperandVal<int>(val)
    {
    }
    
    /**
     * @brief Performs a logical And operations with the rhs
     * @param rhs   Object to be compared with
     * @return Result of a logical And between object and rhs
     */
    virtual bool And(OperandValBase& rhs)
    {
        return m_val && static_cast<IntVal&>(rhs).m_val;
    }
    
    /**
     * @brief Performs a logical Or operations with the rhs
     * @param rhs   Object to tbe compared with
     * @return Reuslt of a logical Or between object and rhs
     */
    virtual bool Or(OperandValBase& rhs)
    {
        return m_val || static_cast<IntVal&>(rhs).m_val;
    }
};

/**
 * @class RegexVal
 * @brief Specializtion for a regular expression value in the expression
 *
 * Regular expresions can be part of the expression and the value of a regular
 * expression will be the compiled regular expression object. Regexp are
 * compared agaings string values. Regular expression match is a seperate 
 * comparison operation like equal to or greate than...
 */
class RegexVal: public OperandValBase
{
 public:
    /**
     * @brief Constructor creates a regular expression value object
     * @param str   Regualr expression patter string, that need to be matched
     */
    RegexVal(const char *str)
        : m_re(str)
    {
    }
    /**
     * @brief Returns the underlying Regular expression object.
     * @return Returns the underlying Regular expression object.
     */
    Regexp& RE()
    {
        return m_re;
    }
 protected:
    Regexp m_re; /**< Regular expression object */
};

/**
 * @class StringVal
 * @brief Specialization for string value types, implementing the match op
 *        for a regular expression, if the rhs is a regular expression
 * 
 * Match operation is specifically for regular expression match. Only string
 * values can match agains a regular expression.If the RHS of a comparison
 * is a regular expression, then instead of other comaprison function pointers
 * the StringVal::Match function pointer is invoked.
 */
class StringVal: public OperandVal<std::string>
{
 public:
    /**
     * @brief String value constructor
     * @param str   c++ string object
     */
    StringVal(const std::string &str)
        : OperandVal<std::string>(str)
    {
    }
    
    /**
     * @brief Matches the StringVal against the regular expression pattern
     * @param rhs   Regular expression values object
     * @return If the regex matches with the StrinVal true is returned else
     *         false is returned.
     */
    virtual bool Match(OperandValBase& rhs)
    {
        int ret = static_cast<RegexVal&>(rhs).RE().Match(m_val);
        return ret > 0;
    }
};

#define VAR_MAX_SUB_ID  8

/**
 * A variable can be of these types. 
 */
enum VarType
{
    VarTypeUnknown,      /**< The type of variable is not known */
    VarTypeGlobal,       /**< The variable scope is global */
    VarTypeLocal,        /**< Variable is local to only the current execution */
    VarTypeLocalPtr,     /**< */
    VarTypeUserDefined,  /**< Variable is application defined*/
};

/**
 * This is the structure that is used to identify a variable. A variable is 
 * divided into two parts
 *  - variable Type identifier
 *  - a vector of integers identfying the variable
 * 
 * This vector is not interpreted by the rule processor. The VarIdentifier is
 * formed by the custom VarHandler and interpreted by the same VarHandler.
 */
struct VarIdentifier
{
    VarType varType;                /**< Variable type */
    uint32_t subId[VAR_MAX_SUB_ID]; /**< Identification vector */
};

// Forward declation for the use of Operand::GetVal()
class RuleRuntime;


/**
 * @class Operand
 * @brief Encapsulation for objects that are being compared
 * 
 * The LHS and RHS of an expression involving an operator is an Operand. The 
 * Operand can have a constant value or its OperandValue might be computed on
 * runtime. If the operands value is computed on runtime it is a VarOperand.
 * 
 * When a rule match is invoked, the rule processor on each RuleAtom invokes the
 * Operand::GetVal() method to get the Operand values to make comparison. If the
 * Operand is a VarOperand, the value is extracted at runtime using the custom
 * VarHandler.
 * 
 * Possible operand type are const int, const string, regex or a variable
 */
class Operand
{
 public:
    /**
     * @brief Default constructor
     * @param type  Type of the operand
     * 
     * This constructor is used by variable operands.
     */
    Operand(Expr::TokenType type = Expr::TypeNone)
        : m_val(NULL),
          m_type(type)
    {
    }
    
    /**
     * @brief Constructor for contant operands 
     * @param val   Value of the operand
     * @param type  Type of the operand
     */
    Operand(OperandValBase *val, Expr::TokenType type)
        : m_val(val),
          m_type(type)
    {
    }
    
    /**
     * @brief Operand destructor
     */
    virtual ~Operand()
    {
        if (m_val) delete m_val;
    }
    
    /**
     * @brief Get the value of the operand
     * @param runTime   For non-constant operands, the value is extracted from
     *                  the runtime
     * @return Returns the value of the operand
     * @see VarOperand, RuleRuntime 
     * 
     * For a constant operand the value at the time of the rule creation is 
     * returned. For Variable operand, this function is overridden by the 
     * VarOperand.
     */
    virtual OperandValBase* GetVal(RuleRuntime *runTime = NULL)
    {
        return m_val;
    }
    
    /**
     * @brief Gets the operand type
     * @return Returns the operand type
     * 
     * Possible values are const int, const string, regex or a variable
     */
    Expr::TokenType GetType()
    {
        return m_type;
    }

 protected:

    /** Value of the operand. This is valid only if the operand is a constant 
     *  value. For variables this value is not set */
    OperandValBase  *m_val;
    
    /** Type of the operand */
    Expr::TokenType m_type;
};

/**
 * @class LocalVarOperand
 * @brief Specialized Operand, that implements a local runtime variable.
 * @see RuleRuntime
 *
 * The LocalVarOperand is used by the RuleAtom, where the value of this operand
 * points to the index of the RuleAtom in the Rule. When a RuleAtom is evaluated
 * the result is stored in the RunTime and the value is identified with the 
 * same index. To fetch the result, from a RuleAtom, the operand value provides
 * the index, using which the result can be obtained from the RunTime
 * 
 */
class LocalVarOperand: public Operand
{
 public:
    /**
     * @brief Constructor that accepts the index of the variable value in the
     *        RuleRuntime
     * @param idx   index to the variable value in the RuleRuntime
     */
    LocalVarOperand(int idx)
        : Operand(new IntVal(idx), Expr::TypeInt)
    {
    }
    
    /**
     * @brief Gets the value of the local variable given the runtime
     * @param runTime   Runtime object that stores the local variable values
     * @return Value of the local variable (this will be an IntVal).
     * 
     * Lookups the RuleRuletime with the index to get the stored result.
     */
    virtual OperandValBase* GetVal(RuleRuntime *runTime = NULL);
};

/**
 * @class VarOperand<AP>
 * @brief Specialization for a user defined variable operand.
 * @see VarIdentifier, RuleRuntime, VarHandler
 * 
 * A user defined variable is identified using a VarIdentifier, which is an
 * opaque sequence of integers, interpreted by the custom implementation.
 * 
 * AP is the custom Access Policy, defined by the RuleTable user, which knows
 * how to access the variable, given the VarIdentifier. AP must implement the
 * method GetVal and have the implementation for accessing the variable from
 * the RuleRuntime. The signature of GetVal is given below
 * @code    
 *  static OperandValBase* GetVal(VarIdentifier &id, RuleRuntime *rt) 
 * @endcode
 * 
 * VarOperand is constructed by the custom VarHandler and the VarHandler also
 * provides the AP (access policy) to access the variable value.
 */
template <typename AP>
class VarOperand: public Operand
{
 public:
    /**
     * @brief Constructor accepting the variable identifier
     * @param id    Id that identifies the variable
     * 
     * This id is interpreted by the AP::GetVal()
     */
    VarOperand(VarIdentifier &id)
        : Operand(Expr::TypeVar)
    {
        memcpy(&m_id, &id, sizeof(m_id));
    }
    
    /**
     * @brief Empty Destructor
     */
    virtual ~VarOperand() {}

    /**
     * @brief Gets the value of the variable from the RuleRunTime
     * @param runTime   runtime object from which the value of the variable is
     *                  to be extracted.
     * @return Value of the variable.
     */
    virtual OperandValBase* GetVal(RuleRuntime *runTime = NULL)
    {
        return AP::GetVal(m_id, runTime);
    }
    
 protected:
    /** Sequence of integers that is used to get the variable value */
    VarIdentifier m_id;
};


/**
 * @class RuleAtom
 * @brief Encapsulation for evaluating the smallest unit of an expression
 *
 * A rule is composed of a sequence of RuleAtoms arranged in postfix order. A
 * RuleAtom has LHS operand, RHS operand and the operation to be performed. The
 * result of a RuleAtom evaluation is stored in the RuleRuntime identified by
 * the index same as the RuleAtom's index in the Rule object.
 * 
 * The LHS and the RHS in case of a logical operation are going to be other
 * RuleAtom objects, that were inserted into the Rule before the logical op
 * RuleAtom object is inserted into the Rule.
 */
class RuleAtom: public LocalVarOperand
{
 public:
    static const short RuleInvalidJump = -1;

    /**
     * @brief Creates RuleAtom
     * @param idx   Index of the RuleAtom ins the Rule object table
     * @param lhs   LHS operand
     * @param rhs   RHS operand
     * @param op    the logical/relational operand for the expression
     * 
     * Based on the operation, a functor for the operation is also initialized.
     */
    RuleAtom(int idx, Operand *lhs, Operand *rhs, int op)
        : LocalVarOperand(idx),
          m_lhs(lhs),
          m_rhs(rhs),
          m_op(op),
          m_andFailJump(RuleInvalidJump),
          m_orPassJump(RuleInvalidJump)
    {
        m_opFunctor = OpFunctorAccess::Get(op);
    }
    
    /**
     * @brief Destructor for the RuleAtom
     */
    ~RuleAtom()
    {
        // For a logical operation, the lhs and rhs are going to be another
        // RuleAtom. These RuleAtom are deleted when the Rule is destroyed.
        if (!IsLogical(m_op))
        {
            delete m_lhs;
            delete m_rhs;
        }
    }
    
    /**
     * @brief Evaluates the LHS and RHS with the operator and returns the result 
     * @param runTime   runtime object from which the values are extracted
     * @return If the operation on the values yields success true is returned
     *         else false is returned.
     */
    bool Evaluate(RuleRuntime *runTime)
    {
        int result = false;
        OperandValBase* lhsVal = m_lhs->GetVal(runTime);
        OperandValBase* rhsVal = m_rhs->GetVal(runTime);

        // Only lhs is considered to be a variable type, sometimes if the
        // variable value could not be found, NULL is returned
        if (lhsVal)
        {
            result = (lhsVal->*m_opFunctor)(*rhsVal);

            if (m_lhs->GetType() == Expr::TypeVar)
            {
                // For user variables, the value is dynamically allocated
                delete lhsVal;
            }
        }

        return result;
    }
    /**
     * @brief Set the jump index to jump-to if the And operation fails
     * @param jumpIdx   Jump index to jump-to on a failed And operation
     * 
     * This is set when the Rule is being created.
     */
    void AndFailJump(short jumpIdx)
    {
        m_andFailJump = jumpIdx;
    }
    
    /**
     * @brief Get the jump index to jumpt-to if the And operation fails
     * @return Returns the jump index
     * 
     * This is be invoked when the rule is being evaluated.
     */
    const short& AndFailJump() const
    {
        return m_andFailJump;
    }
    
    /**
     * @brief Sets the jump index to jump-to if the Or operation is successful 
     * @param jumpIdx   Jump index to jump-to
     * 
     * This will be set when the Rule is being created.
     */
    void OrPassJump(short jumpIdx)
    {
        m_orPassJump = jumpIdx;
    }
    
    /**
     * @brief Gets the jump index to jump-to if the Or operation is successful
     * @return Returns the jump index to jump-to
     */
    const short& OrPassJump() const
    {
        return m_orPassJump;
    }
    
 protected:
    
    /** LHS operand. This can also be another RuleAtom object */
    Operand *m_lhs;
    
    /** RHS operand. This can also be another RuleAtom object */
    Operand *m_rhs;
    
    /** Function pointer to evaluate the operator */
    OpFunctor m_opFunctor;
    int m_op;            /**< Operation being performed */

    short m_andFailJump; /**< Jump-to index if And op returns false*/
    short m_orPassJump;  /**< Jump-to index if Or op returns true */
};

/** 
 * If a rule is matched, this structure is returned providing the matched
 * rule-name and any user data associated with the Rule.
 */
struct RuleMatch
{
    std::string ruleName;
    void *userData;
};


/**
 * @class Rule
 * @brief Encapsulation that stores and evaluates an expression.
 *
 * Internally a Rule is a list of RuleAtoms stored in a postfix form. The atoms
 * are stored in postfix form to evaluate the expression in the right precedence
 * and order.
 * 
 * A rule is identified with a ruleId, which is an unique integer. The priority
 * is used to resolve conflicts in case multiple rules matches. For display 
 * purosed a string name is also associated with the Rule. An opaque userdata
 * can be passed to the rule and the same will be returned back to the user if
 * the rule matches.
 */
class Rule
{
 public:
    static const unsigned RULE_MAX_ATOM = 64;
    
    /**
     * @brief Rule constructor
     * @param name      Name if the rule
     * @param ruleId    Unique id identifying the rule
     * @param priority  priority of the rule
     * @param data      User data associated with the rule
     */
    Rule(const char* name, uint16_t ruleId, uint16_t priority, void *data = NULL);
    
    
    /**
     * @brief Rule destructor, where all the rule atoms are deleted
     */
    ~Rule();

    /**
     * @brief Adds a RuleAtom to the rule list
     * @param lhs   LHS Operand
     * @param rhs   RHS operand
     * @param op    Operation type
     * @return Returs the number of RuleAtoms in the list currently
     */
    int AddAtom(Operand *lhs, Operand *rhs, int op)
    {
        m_atoms.push_back(new RuleAtom(m_atoms.size(), lhs, rhs, op));
        return m_atoms.size() -1;
    }

    /**
     * @brief Given the index, get the RuleAtom object at the index
     * @param idx   index from the RuleAtom object is extracted
     * @return Returns the RuleAtom object at the index
     */
    RuleAtom* GetAtomAt(int idx)
    {
        return m_atoms[idx];
    }

    /**
     * @brief Get the rule id
     * @return Retuns the rule id
     */
    unsigned GetRuleId()
    {
        return m_ruleId;
    }

    /**
     * @brief  Gets the user data associated with the rule
     * @return Returns the user data.
     */
    void* GetData()
    {
        return m_ruleData;
    }

    /**
     * @brief Gets the display name of the rule.
     * @return Returns the name if the rule.
     */
    std::string& Name()
    {
        return m_name;
    }

    /**
     * @brief Evaluates the rule atoms one by one
     * @param rt    Runtime used to extract variable values for comparison
     * @return If the expression evaluated to true the same is returned, else
     *         false is returned.
     */
    bool Evaluate(RuleRuntime *rt);

 protected:
    typedef std::vector<RuleAtom*> RuleAtomList;
    
    uint16_t m_ruleId;      /**< Unique id of the rule */
    uint16_t m_priority;    /**< Priority of the rule */

    RuleAtomList m_atoms;   /**< RuleAtoms in postfix order */

    std::string m_name;     /**< Display name of the rule */
    void* m_ruleData;       /**< User data associated with the rule */
};

/**
 * @class VarHandler
 * @brief Abstraction to enable custom variable interpretation
 * 
 * Provides a hook to construct an Operand from the expression string. The
 * access policy is specified while constructing the Operand. The VarHandler is
 * registered with the RuleTable for a given protocol.
 */
class VarHandler
{
 public:
    virtual ~VarHandler() {}

    /**
     * @brief Pure virtual function, to be implemented by the custom variable 
     *        interpreter
     * @param [in]  str     string to be interpreted into VarIdentifier
     * @param [out] varId   constrcuted variable identifier for the string
     * @return Constructed Operand object with the specified access policy.
     */
    virtual Operand* ConstructOperand(std::string &str, VarIdentifier &varId) = 0;
};


/**
 * @class RuleTable
 * @brief Encapsulation for the table of Rule objects
 * 
 * The rule processing logic and the rule addition and deletion logic is 
 * performed in the RuleTable. The custom VarHandler also registers with this
 * RuleTable.
 */
class RuleTable
{
 public:
    /**
     * @brief Constructor for RuleTable
     */
    RuleTable();
    
    /**
     * @brief Desctructor
     */
    ~RuleTable();

    /**
     * @brief Copy constructor
     * @param rTable    RHS RuleTable object
     */
    RuleTable(RuleTable &rTable);

    /**
     * @brief Register the VarHandler for the given protocol prefix
     * @param str       protocol prefix string
     * @param handler   Custom protocol VarHandler object
     * @return Returns 0 on success
     * @see VarHandler
     */
    unsigned RegisterVarHandler(const char* str, VarHandler *handler)
    {
        VarHandlerTable::iterator it = m_varHandlerTable.find(str);
        if (it != m_varHandlerTable.end())
        {
            throw RuleException("Duplicate Var Handler in rule table");
        }
        m_varHandlerTable[str] = handler;
        return 0;
    }

    /**
     * @brief Add a rule to the rule table
     * @param name      Name of the rule
     * @param ruleId    Unique id to identify the rule
     * @param priority  Priority of the rule
     * @param expr      Expression as parsed by the ExprParser
     * @param data      User data associated with the rule
     * 
     * When the rule match is found the user data is also returned.
     */
    void AddRule(const char* name, uint16_t ruleId, uint16_t priority, 
                 ExprRef &expr, void *data = NULL);

    /**
     * @brief Remove a rule from the rule table
     * @param ruleId    Rule id to be removed
     * @param priority  Priroity of the rule to be removed
     */
    void RemoveRule(uint16_t ruleId, uint16_t priority)
    {
        ScopedWriteLock lock(m_rulesLock);

        unsigned key = ruleId | (priority << 16);
        RulesMap::iterator it = m_rules.find(key);
        if (it != m_rules.end())
        {
            delete it->second;
            m_rules.erase(it);
        }
    }

    /**
     * @brief Removes all the rules from the RuleTable
     */
    void Flush();

    /**
     * @brief Matches the first rule that evaluates to true
     * @param [in]  rt            RuleRuntime object
     * @param [out] singleMatch   Matched rule identifier
     * @return If a rule is matched returns true, else false.
     */
    bool Match(RuleRuntime *rt, RuleMatch &singleMatch);

    /**
     * @brief Returns all the rules that matches for the RunTime values
     * @param [in]  rt          RuleRuntime object
     * @param [out] multiMatch  Matched rules as a vector    
     * @return Returns the number of rules matched
     * 
     * The list of Rules returned are sorted based on the priority.
     */
    int Match(RuleRuntime *rt, std::vector<RuleMatch>& multiMatch);

 protected:
    /**
     * @brief Constructs a Rule with RuleAtoms in postfix order
     * @param rule  Rule to which the ExprRef is to be added in postfix order
     * @param expr  Expression tree as parsed by ExprParser
     * @return Number of RuleAtoms added to the Rule
     */
    int ConstructPostFix(Rule *rule, ExprRef &expr);
    
    /**
     * @brief Constructs the Operand object based on the Operand type
     * @param term  Terminal expression, which is the Operand
     * @return Constructed Operand object.
     * 
     * For const Operands, the RuleTable constructs the corresponding Operands.
     * If the Operand is a user defined VarType, then the registered VarHandler
     * is invoked to construct the Operand.
     */
    Operand* ConstructOperand(ExprRef &term);

    // The key is 16bit priority and 16bit ruleid
    // The main critieria to go for map is because of inbuilt sorting
    typedef std::map<uint32_t, Rule*> RulesMap;
    typedef std::unordered_map<std::string, VarHandler*> VarHandlerTable;
    
    RulesMap m_rules;       /**< Rules in a sorted map */
    RWLock   m_rulesLock;   /**< Lock associated with the RulesMap */

    VarHandlerTable m_varHandlerTable;  /**< Registered VarHandlers */
};

// this runtime should be a per thread data
/**
 * @class RuleRuntime
 * @brief Encasulation that stores the runtime information while executing rules
 * 
 * RuleRuntime is used to store
 *  - The protocol message as user data - RuleRuntime::UserData()
 *  - Temporary evaluation results per RuleAtom within a Rule
 * 
 * This runtime object is passed to the custom VarHandler to get the values to do
 * a rule match. This should be stored as a per thread object and the user data 
 * and temporary evaluations results are invalid after a RuleTable match. In 
 * other words, the runtime data is valid only per thread and valid only during
 * a Rule match.
 */
class RuleRuntime
{
 public:
    /**
     * @brief RuleRuntime constructor
     * @param m_rt  RuleTable object
     */
    RuleRuntime(RuleTable *m_rt = NULL)
        : m_ruleTable(m_rt),
          m_curRule(NULL),
          m_userData(NULL),
          m_ruleStack(NULL)
    {
    }
    
    /**
     * @brief Destructor
     */
    ~RuleRuntime()
    {
    }
    
    /**
     * @brief Gets the RuleTable object
     * @return RuleTable object
     */
    RuleTable& GetRuleTable()
    {
        return *m_ruleTable;
    }

    /**
     * @brief Gets the current rule that is being executed
     * @return Current Rule object
     */
    Rule* CurrentRule()
    {
        return m_curRule;
    }
    
    /**
     * @brief Sets the current rule that is being executed
     * @param rule  Current rule object
     * @see RuleTable::Match()
     * 
     * This is set by the RuleTable.
     */
    void CurrentRule(Rule* rule)
    {
        m_curRule = rule;
    }

    /**
     * @brief Get the userdata, that will be available for the custom VarHandler
     * @return Custom user data pointer
     * 
     * Usually the message from which the values are to be extracted is set as
     * the user data.
     */
    void* UserData()
    {
        return m_userData;
    }
    
    /**
     * @brief Sets the userdata, that will be available for the custom VarHandler
     * @param data  Custom user data
     */
    void UserData(void *data)
    {
        m_userData = data;
    }

    /**
     * @brief Set the temporary rule evaluation result for a RuleAtom
     * @param atomIdx   Index of the RuleAtom within the Rule
     * @param result    Result value (true/false)
     * @see RuleAtom
     */
    void SetResult(int atomIdx, int result)
    {
        m_ruleStack[atomIdx].Set(result);
    }

    /**
     * @brief Get the temorary rule evaluation result associated with a RuleAtom
     * @param atomIdx   RuleAtom index within the Rule
     * @return Result of the evaluation for the rule index
     * @see RuleAtom
     */
    int GetResult(int atomIdx)
    {
        return m_ruleStack[atomIdx].Get();
    }
    /**
     * @brief Gets the OperandVal object given the index of the RuleAtom within
     *        a Rule
     * @param atomIdx   Index of RuleAtom within the Rule
     * @return OperandVal that provides stores the result of the rule 
     * @see RuleAtom, Operand::GetVal(), LocalVarOperand::GetVal()
     */
    OperandValBase* GetOperandVal(int atomIdx)
    {
        return &(m_ruleStack[atomIdx]);
    }

    /**
     * @brief Creates storage for local variables for the current Rule execution
     * @param p     Address on which the local variables are to be stored
     * @param sz    Number of local variables to be allocated
     * 
     * The pointer 'p' is passed, to avoid any heap memory allocation. The
     * memory is allocated in the stack and passed to this method. It was 
     * observed that, this improves the performance by 30-50%
     */
    void PushRuleStack(void *p, int sz)
    {
        m_ruleStack = new(p) IntVal[sz];
    }

    /**
     * @brief Cleans up the stack after a rule execution
     */
    void PopRuleStack()
    {
        // Since the memory is allocated in stack, no need to free
        // Present as a place holder for future cleanup stack cleanup operations
    }


 protected:
    RuleTable* m_ruleTable; /**< Loose reference to RuleTable object */
    Rule* m_curRule;        /**< Current rule that is being executed */
    void* m_userData;       /**< Userdata required by the custom VarHandler */
    
    IntVal* m_ruleStack;    /**< Temporary data, for each rule execution */
};

} // namespace eAccelero

#endif

