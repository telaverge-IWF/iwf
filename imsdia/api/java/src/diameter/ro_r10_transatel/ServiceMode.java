package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Service-Mode  AVP (AVP Code 2032) is of type Unsigned32and provides the 
 * mode for  CDIV, CB and ECT MMTel supplementary services
 */
public class ServiceMode extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a ServiceMode with the given value.
     *
     * @param value - the value of the AVP
     */
    public ServiceMode(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    ServiceMode(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
