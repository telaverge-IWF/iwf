package diameter.ro_r10;

import com.intellinet.diameter.*;


/** 
  * The Node-Id AVP (AVP code 2064) is of type UTF8String and includes an 
  * optional, operator configurable identifier string for the node that had 
  * generated the Accounting Request (ACR). 
  */
public class NodeId extends com.intellinet.diameter.DerivedAVP<String> {
    /**
     * Constructs a NodeId with the given value.
     *
     * @param value - the value of the AVP
     */
    public NodeId(String value) {
        super(new com.intellinet.diameter.UTF8StringData(value));
    }

    NodeId(com.intellinet.diameter.UTF8StringData data) {
        super(data);
    }
}
