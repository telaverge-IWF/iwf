package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Final-Unit-Indication AVP (AVP Code 430) is of type Grouped and indicates that 
 * the Granted-Service-Unit AVP in the Credit-Control-Answer, or in the AA answer, 
 * contains the final units for the service. After these units have expired, the Diameter 
 * credit-control client is responsible for executing the action indicated in the
 * Final-Unit-Action AVP.
 */
public class FinalUnitIndication extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new FinalUnitIndication.
     */
    public FinalUnitIndication() {}

    FinalUnitIndication(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Gets the FinalUnitAction.
     */
    public FinalUnitAction getFinalUnitAction() throws NoSuchAttributeException {
        return (FinalUnitAction)_data.getContainer().get(Ro_r10_transatelAttributeName.FinalUnitAction, 0);
    }

    /**
     * Sets the FinalUnitAction.
     *
     * @param avp - the attribute value
     */
    public void setFinalUnitAction(FinalUnitAction avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.FinalUnitAction, avp.getData(), true);
    }

    /**
     * Returns number of RestrictionFilterRule instances.
     */
    public int countRestrictionFilterRule() {
        return _data.getContainer().count(Ro_r10_transatelAttributeName.RestrictionFilterRule);
    }

    /**
     * Gets one RestrictionFilterRule.
     *
     * @param index - the index of the attribute to return
     */
    public RestrictionFilterRule getRestrictionFilterRule(int index) throws NoSuchAttributeException {
        return (RestrictionFilterRule)_data.getContainer().get(Ro_r10_transatelAttributeName.RestrictionFilterRule, index);
    }

    /**
     * Adds one RestrictionFilterRule.
     *
     * @param avp - the attribute value
     */
    public void addRestrictionFilterRule(RestrictionFilterRule avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.RestrictionFilterRule, avp.getData(), false);
    }

    /**
     * Returns number of FilterId instances.
     */
    public int countFilterId() {
        return _data.getContainer().count(diameter.nasreq.NasreqAttributeName.FilterId);
    }

    /**
     * Gets one FilterId.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.nasreq.FilterId getFilterId(int index) throws NoSuchAttributeException {
        return (diameter.nasreq.FilterId)_data.getContainer().get(diameter.nasreq.NasreqAttributeName.FilterId, index);
    }

    /**
     * Adds one FilterId.
     *
     * @param avp - the attribute value
     */
    public void addFilterId(diameter.nasreq.FilterId avp) {
        _data.getContainer().add(diameter.nasreq.NasreqAttributeName.FilterId, avp.getData(), false);
    }

    /**
     * Tests whether there is any RedirectServer.
     */
    public boolean containsRedirectServer() {
        return _data.getContainer().contains(Ro_r10_transatelAttributeName.RedirectServer);
    }

    /**
     * Gets the RedirectServer.
     */
    public RedirectServer getRedirectServer() throws NoSuchAttributeException {
        return (RedirectServer)_data.getContainer().get(Ro_r10_transatelAttributeName.RedirectServer, 0);
    }

    /**
     * Sets the RedirectServer.
     *
     * @param avp - the attribute value
     */
    public void setRedirectServer(RedirectServer avp) {
        _data.getContainer().add(Ro_r10_transatelAttributeName.RedirectServer, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        sb.append("    FinalUnitAction:");
            try {
                sb.append(getFinalUnitAction()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        for (int i = 0; i < countRestrictionFilterRule(); ++i) {
            sb.append("    RestrictionFilterRule:");
            try {
                sb.append(getRestrictionFilterRule(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countFilterId(); ++i) {
            sb.append("    FilterId:");
            try {
                sb.append(getFilterId(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRedirectServer()) {
            sb.append("    RedirectServer:");
            try {
                sb.append(getRedirectServer()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
