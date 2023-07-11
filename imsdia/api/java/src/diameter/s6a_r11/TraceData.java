package diameter.s6a_r11;

import com.intellinet.diameter.*;


public class TraceData extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new TraceData.
     */
    public TraceData() {}

    TraceData(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the TraceReference.
     */
    public TraceReference getTraceReference() throws NoSuchAttributeException {
        return (TraceReference)_data.getContainer().get(S6a_r11AttributeName.TraceReference, 0);
    }

    /**
     * Sets the TraceReference.
     *
     * @param avp - the attribute value
     */
    public void setTraceReference(TraceReference avp) {
        _data.getContainer().add(S6a_r11AttributeName.TraceReference, avp.getData(), true);
    }

    /**
     * Gets the TraceDepth.
     */
    public TraceDepth getTraceDepth() throws NoSuchAttributeException {
        return (TraceDepth)_data.getContainer().get(S6a_r11AttributeName.TraceDepth, 0);
    }

    /**
     * Sets the TraceDepth.
     *
     * @param avp - the attribute value
     */
    public void setTraceDepth(TraceDepth avp) {
        _data.getContainer().add(S6a_r11AttributeName.TraceDepth, avp.getData(), true);
    }

    /**
     * Gets the TraceNETypeList.
     */
    public TraceNETypeList getTraceNETypeList() throws NoSuchAttributeException {
        return (TraceNETypeList)_data.getContainer().get(S6a_r11AttributeName.TraceNETypeList, 0);
    }

    /**
     * Sets the TraceNETypeList.
     *
     * @param avp - the attribute value
     */
    public void setTraceNETypeList(TraceNETypeList avp) {
        _data.getContainer().add(S6a_r11AttributeName.TraceNETypeList, avp.getData(), true);
    }

    /**
     * Gets the TraceEventList.
     */
    public TraceEventList getTraceEventList() throws NoSuchAttributeException {
        return (TraceEventList)_data.getContainer().get(S6a_r11AttributeName.TraceEventList, 0);
    }

    /**
     * Sets the TraceEventList.
     *
     * @param avp - the attribute value
     */
    public void setTraceEventList(TraceEventList avp) {
        _data.getContainer().add(S6a_r11AttributeName.TraceEventList, avp.getData(), true);
    }

    /**
     * Gets the TraceCollectionEntity.
     */
    public TraceCollectionEntity getTraceCollectionEntity() throws NoSuchAttributeException {
        return (TraceCollectionEntity)_data.getContainer().get(S6a_r11AttributeName.TraceCollectionEntity, 0);
    }

    /**
     * Sets the TraceCollectionEntity.
     *
     * @param avp - the attribute value
     */
    public void setTraceCollectionEntity(TraceCollectionEntity avp) {
        _data.getContainer().add(S6a_r11AttributeName.TraceCollectionEntity, avp.getData(), true);
    }

    /**
     * Tests whether there is any TraceInterfaceList.
     */
    public boolean containsTraceInterfaceList() {
        return _data.getContainer().contains(S6a_r11AttributeName.TraceInterfaceList);
    }

    /**
     * Gets the TraceInterfaceList.
     */
    public TraceInterfaceList getTraceInterfaceList() throws NoSuchAttributeException {
        return (TraceInterfaceList)_data.getContainer().get(S6a_r11AttributeName.TraceInterfaceList, 0);
    }

    /**
     * Sets the TraceInterfaceList.
     *
     * @param avp - the attribute value
     */
    public void setTraceInterfaceList(TraceInterfaceList avp) {
        _data.getContainer().add(S6a_r11AttributeName.TraceInterfaceList, avp.getData(), true);
    }

    /**
     * Tests whether there is any OMCId.
     */
    public boolean containsOMCId() {
        return _data.getContainer().contains(S6a_r11AttributeName.OMCId);
    }

    /**
     * Gets the OMCId.
     */
    public OMCId getOMCId() throws NoSuchAttributeException {
        return (OMCId)_data.getContainer().get(S6a_r11AttributeName.OMCId, 0);
    }

    /**
     * Sets the OMCId.
     *
     * @param avp - the attribute value
     */
    public void setOMCId(OMCId avp) {
        _data.getContainer().add(S6a_r11AttributeName.OMCId, avp.getData(), true);
    }

    /**
     * Tests whether there is any MDTConfiguration.
     */
    public boolean containsMDTConfiguration() {
        return _data.getContainer().contains(S6a_r11AttributeName.MDTConfiguration);
    }

    /**
     * Gets the MDTConfiguration.
     */
    public MDTConfiguration getMDTConfiguration() throws NoSuchAttributeException {
        return (MDTConfiguration)_data.getContainer().get(S6a_r11AttributeName.MDTConfiguration, 0);
    }

    /**
     * Sets the MDTConfiguration.
     *
     * @param avp - the attribute value
     */
    public void setMDTConfiguration(MDTConfiguration avp) {
        _data.getContainer().add(S6a_r11AttributeName.MDTConfiguration, avp.getData(), true);
    }

    /**
     * Returns number of extra AVP instances.
     */
    public int countExtra() {
        return _data.getContainer().count(AttributeName.AVP);
    }

    /**
     * Returns number of extra AVP instances that match the given attribute name.
     *
     * @param name - the attribute to count
     */
    public int countExtra(AttributeName name) {
        return _data.getContainer().countExtra(name);
    }

    /**
     * Gets an extra AVP that matches the given attribute name.
     *
     * @param name - the attribute to return
     * @param index - the index of the attribute to return
     */
    public AVP getExtra(AttributeName name, int index) throws NoSuchAttributeException {
        return _data.getContainer().getExtra(name, index);
    }

    /**
     * Adds one extra AVP.
     *
     * @param avp - the attribute value
     */
    public void addExtra(AVP avp) {
        _data.getContainer().add(AttributeName.AVP, avp.getData(), false);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    TraceReference:");
            try {
                sb.append(getTraceReference()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    TraceDepth:");
            try {
                sb.append(getTraceDepth()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    TraceNETypeList:");
            try {
                sb.append(getTraceNETypeList()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    TraceEventList:");
            try {
                sb.append(getTraceEventList()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    TraceCollectionEntity:");
            try {
                sb.append(getTraceCollectionEntity()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsTraceInterfaceList()) {
            sb.append("    TraceInterfaceList:");
            try {
                sb.append(getTraceInterfaceList()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOMCId()) {
            sb.append("    OMCId:");
            try {
                sb.append(getOMCId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsMDTConfiguration()) {
            sb.append("    MDTConfiguration:");
            try {
                sb.append(getMDTConfiguration()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }
}
