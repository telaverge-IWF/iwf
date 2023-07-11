package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * Content-Class AVP is of type Enumerated and classifies the content of the MM to the highest content 
 * class to which the MM belongs, as defined in MMS Encapsulation.
 */
public class ContentClass extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        text(0),
        image_basic(1),
        image_rich(2),
        video_basic(3),
        video_rich(4),
        megapixel(5),
        content_basic(6),
        content_rich(7);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a ContentClass with the given value.
     *
     * @param value - the value of the AVP
     */
    public ContentClass(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    ContentClass(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
