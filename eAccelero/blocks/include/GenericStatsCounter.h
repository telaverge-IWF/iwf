#ifndef __GENERIC_STATSCOUNTER_H__
#define __GENERIC_STATSCOUNTER_H__

namespace eAccelero {

class GenericStatsCounter {

    public:

        friend uint64_t collateStats(GenericStatsCounter *stats);
        
        friend void ResetGenericStatsCounter(GenericStatsCounter *stats);

        GenericStatsCounter() {
            m_count = 0;
        }

        void Increment() {
            m_count++;
        }

        bool Add(uint64_t count) {
            if (count <= 0) {
                return false;
            }

            m_count += count;
            return true;
        }

        void Reset() {
            m_count = 0;
        }

        uint64_t GetCount() {
            return m_count;
        }
        
        void Decrement() {
            m_count--;
        }

    private:
        uint64_t m_count;
};
};//namespace eAccelero
#endif
