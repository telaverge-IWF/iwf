package diameter.cxdx_v12;

import com.intellinet.diameter.*;


public class FramedInterfaceId extends com.intellinet.diameter.DerivedAVP<Long> {
    /**
     * Constructs a FramedInterfaceId with the given value.
     *
     * @param value - the value of the AVP
     */
    public FramedInterfaceId(Long value) {
        super(new com.intellinet.diameter.Unsigned64Data(value));
    }

    FramedInterfaceId(com.intellinet.diameter.Unsigned64Data data) {
        super(data);
    }
}
