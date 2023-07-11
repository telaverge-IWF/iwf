package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
* The Transcoder-Inserted-Indication  AVP (AVP code 2605) is of type Enumerated and indicates
* if a transcoder is inserted or not for the SDP media component.
*/
public class TranscoderInsertedIndication extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        Transcoder_Not_Inserted(0),
        Transcoder_Inserted(1);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a TranscoderInsertedIndication with the given value.
     *
     * @param value - the value of the AVP
     */
    public TranscoderInsertedIndication(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    TranscoderInsertedIndication(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
