package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Tunnel-Preference AVP (AVP Code 83) is of type Unsigned32 and is
 * used to identify the relative preference assigned to each tunnel when
 * more than one set of tunneling AVPs is returned within separate
 * Grouped-AVP AVPs. It MAY be used in an authorization request as a
 * hint to the server that a specific preference is desired, but the
 * server is not required to honor the hint in the corresponding response.
 */
public class TunnelPreference extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a TunnelPreference with the given value.
     *
     * @param value - the value of the AVP
     */
    public TunnelPreference(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    TunnelPreference(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
