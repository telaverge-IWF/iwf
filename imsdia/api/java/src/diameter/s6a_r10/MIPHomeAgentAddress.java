package diameter.s6a_r10;

import com.intellinet.diameter.*;


public class MIPHomeAgentAddress extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a MIPHomeAgentAddress with the given value.
     *
     * @param value - the value of the AVP
     */
    public MIPHomeAgentAddress(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    MIPHomeAgentAddress(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
