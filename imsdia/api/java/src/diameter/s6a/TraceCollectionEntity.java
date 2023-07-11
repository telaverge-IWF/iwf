package diameter.s6a;

import com.intellinet.diameter.*;


public class TraceCollectionEntity extends com.intellinet.diameter.DerivedAVP<Address> {
    /**
     * Constructs a TraceCollectionEntity with the given value.
     *
     * @param value - the value of the AVP
     */
    public TraceCollectionEntity(Address value) {
        super(new com.intellinet.diameter.AddressData(value));
    }

    TraceCollectionEntity(com.intellinet.diameter.AddressData data) {
        super(data);
    }
}
