package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Event-Charging-TimeStamp AVP (AVP code 1258) is of type Time, and it 
 * holds the timestamp of the event reported in the CC-Service-Specific-Units 
 * AVP when event based charging applies. 
 */
public class EventChargingTimeStamp extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a EventChargingTimeStamp with the given value.
     *
     * @param value - the value of the AVP
     */
    public EventChargingTimeStamp(Integer value) {
        super(new com.intellinet.diameter.TimeData(value));
    }

    EventChargingTimeStamp(com.intellinet.diameter.TimeData data) {
        super(data);
    }
}
