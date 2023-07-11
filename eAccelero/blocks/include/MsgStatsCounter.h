#ifndef __MSG_STATSCOUNTER_H__
#define __MSG_STATSCOUNTER_H__

namespace eAccelero {

class MsgStatsCounter {
    public:
        friend MsgStatsCounter collateMsgStatsCounter(MsgStatsCounter *stats);
        friend void ResetMsgStatsCounter(MsgStatsCounter *stats);
        MsgStatsCounter() {
            rxReqCount =0;
            rxRspCount =0;
            txReqCount =0;
            txRspCount =0;
        }

        void IncrementRxReqCount() {
            rxReqCount++;
        }

        void IncrementRxRspCount() {
            rxRspCount++;
        }

        void IncrementTxReqCount() {
            txReqCount++;
        }

        void IncrementTxRspCount() {
            txRspCount++;
        }

        void DecrementRxReqCount() {
            rxReqCount--;
        }

        void DecrementRxRspCount() {
            rxRspCount--;
        }

        void DecrementTxReqCount() {
            txReqCount--;
        }

        void DecrementTxRspCount() {
            txRspCount--;
        }

        void Reset() {
            rxReqCount =0;
            rxRspCount =0;
            txReqCount =0;
            txRspCount =0;
        }

        uint64_t GetRxReqCount() {
            return rxReqCount;
        }

        uint64_t GetRxRspCount() {
            return rxRspCount;
        }

        uint64_t GetTxReqCount() {
            return txReqCount;
        }

        uint64_t GetTxRspCount() {
            return txRspCount;
        }

    private:
        uint64_t rxReqCount;
        uint64_t rxRspCount;
        uint64_t txReqCount;
        uint64_t txRspCount;
};

};//namespace eAccelero
#endif
