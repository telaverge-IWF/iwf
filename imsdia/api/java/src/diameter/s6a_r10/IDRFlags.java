package diameter.s6a_r10;

import com.intellinet.diameter.*;


/**
  *The IDR-Flags AVP is of type Unsigned32 and it shall contain a bit mask. 
  *The meaning of the bits shall be as defined in table 7.3.103/1:
  */
public class IDRFlags extends com.intellinet.diameter.DerivedAVP<Integer> {
    /**
     * Constructs a IDRFlags with the given value.
     *
     * @param value - the value of the AVP
     */
    public IDRFlags(Integer value) {
        super(new com.intellinet.diameter.Unsigned32Data(value));
    }

    IDRFlags(com.intellinet.diameter.Unsigned32Data data) {
        super(data);
    }
}
