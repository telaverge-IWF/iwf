package diameter.nasreq;

import com.intellinet.diameter.*;


/**
 * The Originating-Line-Info AVP (AVP Code 94) is of type OctetString
 * and is sent by the NAS system to convey information about the origin
 * of the call from an SS7 system.
 * The originating line information (OLI) element indicates the nature
 * and/or characteristics of the line from which a call originated
 * (e.g., pay phone, hotel, cellular). Telephone companies are starting
 * to offer OLI to their customers as an option over Primary Rate
 * Interface (PRI). Internet Service Providers (ISPs) can use OLI in
 * addition to Called-Station-Id and Calling-Station-Id attributes to
 * differentiate customer calls and to define different services.
 * The Value field contains two octets (00 - 99).
 */
public class OriginatingLineInfo extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a OriginatingLineInfo with the given value.
     *
     * @param value - the value of the AVP
     */
    public OriginatingLineInfo(String value) {
        super(new com.intellinet.diameter.OctetStringData(value));
    }

    OriginatingLineInfo(com.intellinet.diameter.OctetStringData data) {
        super(data);
    }
}
