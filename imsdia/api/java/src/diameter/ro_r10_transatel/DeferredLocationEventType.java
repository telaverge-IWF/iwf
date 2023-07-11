package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Deferred-Location-Event-Type AVP is of type UTF8String and holds information related to a deferred
 * location request.
 */
public class DeferredLocationEventType extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a DeferredLocationEventType with the given value.
     *
     * @param value - the value of the AVP
     */
    public DeferredLocationEventType(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    DeferredLocationEventType(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
