package diameter.s13_r10;

import com.intellinet.diameter.*;

/**
 * This class defines singleton AttributeName instances for all attributes in <i><b>s13_r10</b></i>.
 */
public abstract class S13_r10AttributeName {

    private static class EquipmentStatusAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new EquipmentStatus((com.intellinet.diameter.EnumeratedData)impl);
        }
    }

    public static final AttributeName EquipmentStatus = new com.intellinet.diameter.EnumeratedName("Equipment-Status", new EquipmentStatusAVPBuilder());

    private static class TerminalInformationAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new TerminalInformation((com.intellinet.diameter.GroupedData)impl);
        }
    }

    public static final AttributeName TerminalInformation = new com.intellinet.diameter.GroupedName("Terminal-Information", new TerminalInformationAVPBuilder());

    private static class IMEIAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new IMEI((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName IMEI = new com.intellinet.diameter.UTF8StringName("IMEI", new IMEIAVPBuilder());

    private static class S133GPP2MEIDAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new S133GPP2MEID((com.intellinet.diameter.OctetStringData)impl);
        }
    }

    public static final AttributeName S133GPP2MEID = new com.intellinet.diameter.OctetStringName("S13-3GPP2-MEID", new S133GPP2MEIDAVPBuilder());

    private static class SoftwareVersionAVPBuilder implements com.intellinet.diameter.AVPBuilder {
        public AVP build(com.intellinet.diameter.Data impl) {
            return new SoftwareVersion((com.intellinet.diameter.UTF8StringData)impl);
        }
    }

    public static final AttributeName SoftwareVersion = new com.intellinet.diameter.UTF8StringName("Software-Version", new SoftwareVersionAVPBuilder());
}

