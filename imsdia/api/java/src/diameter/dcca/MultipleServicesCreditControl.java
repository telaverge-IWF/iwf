package diameter.dcca;

import com.intellinet.diameter.*;


/**
 * Multiple-Services-Credit-Control AVP is of type Grouped and contains the AVPs related 
 * to the independent credit-control of multiple services feature.  Note that each instance of
 * this AVP carries units related to one or more services or related to a single rating group.
 */
public class MultipleServicesCreditControl extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new MultipleServicesCreditControl.
     */
    public MultipleServicesCreditControl() {}

    MultipleServicesCreditControl(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any GrantedServiceUnit.
     */
    public boolean containsGrantedServiceUnit() {
        return _data.getContainer().contains(DccaAttributeName.GrantedServiceUnit);
    }

    /**
     * Gets the GrantedServiceUnit.
     */
    public GrantedServiceUnit getGrantedServiceUnit() throws NoSuchAttributeException {
        return (GrantedServiceUnit)_data.getContainer().get(DccaAttributeName.GrantedServiceUnit, 0);
    }

    /**
     * Sets the GrantedServiceUnit.
     *
     * @param avp - the attribute value
     */
    public void setGrantedServiceUnit(GrantedServiceUnit avp) {
        _data.getContainer().add(DccaAttributeName.GrantedServiceUnit, avp.getData(), true);
    }

    /**
     * Tests whether there is any RequestedServiceUnit.
     */
    public boolean containsRequestedServiceUnit() {
        return _data.getContainer().contains(DccaAttributeName.RequestedServiceUnit);
    }

    /**
     * Gets the RequestedServiceUnit.
     */
    public RequestedServiceUnit getRequestedServiceUnit() throws NoSuchAttributeException {
        return (RequestedServiceUnit)_data.getContainer().get(DccaAttributeName.RequestedServiceUnit, 0);
    }

    /**
     * Sets the RequestedServiceUnit.
     *
     * @param avp - the attribute value
     */
    public void setRequestedServiceUnit(RequestedServiceUnit avp) {
        _data.getContainer().add(DccaAttributeName.RequestedServiceUnit, avp.getData(), true);
    }

    /**
     * Returns number of UsedServiceUnit instances.
     */
    public int countUsedServiceUnit() {
        return _data.getContainer().count(DccaAttributeName.UsedServiceUnit);
    }

    /**
     * Gets one UsedServiceUnit.
     *
     * @param index - the index of the attribute to return
     */
    public UsedServiceUnit getUsedServiceUnit(int index) throws NoSuchAttributeException {
        return (UsedServiceUnit)_data.getContainer().get(DccaAttributeName.UsedServiceUnit, index);
    }

    /**
     * Adds one UsedServiceUnit.
     *
     * @param avp - the attribute value
     */
    public void addUsedServiceUnit(UsedServiceUnit avp) {
        _data.getContainer().add(DccaAttributeName.UsedServiceUnit, avp.getData(), false);
    }

    /**
     * Tests whether there is any TariffChangeUsage.
     */
    public boolean containsTariffChangeUsage() {
        return _data.getContainer().contains(DccaAttributeName.TariffChangeUsage);
    }

    /**
     * Gets the TariffChangeUsage.
     */
    public TariffChangeUsage getTariffChangeUsage() throws NoSuchAttributeException {
        return (TariffChangeUsage)_data.getContainer().get(DccaAttributeName.TariffChangeUsage, 0);
    }

    /**
     * Sets the TariffChangeUsage.
     *
     * @param avp - the attribute value
     */
    public void setTariffChangeUsage(TariffChangeUsage avp) {
        _data.getContainer().add(DccaAttributeName.TariffChangeUsage, avp.getData(), true);
    }

    /**
     * Returns number of ServiceIdentifier instances.
     */
    public int countServiceIdentifier() {
        return _data.getContainer().count(DccaAttributeName.ServiceIdentifier);
    }

    /**
     * Gets one ServiceIdentifier.
     *
     * @param index - the index of the attribute to return
     */
    public ServiceIdentifier getServiceIdentifier(int index) throws NoSuchAttributeException {
        return (ServiceIdentifier)_data.getContainer().get(DccaAttributeName.ServiceIdentifier, index);
    }

    /**
     * Adds one ServiceIdentifier.
     *
     * @param avp - the attribute value
     */
    public void addServiceIdentifier(ServiceIdentifier avp) {
        _data.getContainer().add(DccaAttributeName.ServiceIdentifier, avp.getData(), false);
    }

    /**
     * Tests whether there is any RatingGroup.
     */
    public boolean containsRatingGroup() {
        return _data.getContainer().contains(DccaAttributeName.RatingGroup);
    }

    /**
     * Gets the RatingGroup.
     */
    public RatingGroup getRatingGroup() throws NoSuchAttributeException {
        return (RatingGroup)_data.getContainer().get(DccaAttributeName.RatingGroup, 0);
    }

    /**
     * Sets the RatingGroup.
     *
     * @param avp - the attribute value
     */
    public void setRatingGroup(RatingGroup avp) {
        _data.getContainer().add(DccaAttributeName.RatingGroup, avp.getData(), true);
    }

    /**
     * Returns number of GSUPoolReference instances.
     */
    public int countGSUPoolReference() {
        return _data.getContainer().count(DccaAttributeName.GSUPoolReference);
    }

    /**
     * Gets one GSUPoolReference.
     *
     * @param index - the index of the attribute to return
     */
    public GSUPoolReference getGSUPoolReference(int index) throws NoSuchAttributeException {
        return (GSUPoolReference)_data.getContainer().get(DccaAttributeName.GSUPoolReference, index);
    }

    /**
     * Adds one GSUPoolReference.
     *
     * @param avp - the attribute value
     */
    public void addGSUPoolReference(GSUPoolReference avp) {
        _data.getContainer().add(DccaAttributeName.GSUPoolReference, avp.getData(), false);
    }

    /**
     * Tests whether there is any ValidityTime.
     */
    public boolean containsValidityTime() {
        return _data.getContainer().contains(DccaAttributeName.ValidityTime);
    }

    /**
     * Gets the ValidityTime.
     */
    public ValidityTime getValidityTime() throws NoSuchAttributeException {
        return (ValidityTime)_data.getContainer().get(DccaAttributeName.ValidityTime, 0);
    }

    /**
     * Sets the ValidityTime.
     *
     * @param avp - the attribute value
     */
    public void setValidityTime(ValidityTime avp) {
        _data.getContainer().add(DccaAttributeName.ValidityTime, avp.getData(), true);
    }

    /**
     * Tests whether there is any ResultCode.
     */
    public boolean containsResultCode() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.ResultCode);
    }

    /**
     * Gets the ResultCode.
     */
    public diameter.base.ResultCode getResultCode() throws NoSuchAttributeException {
        return (diameter.base.ResultCode)_data.getContainer().get(diameter.base.BaseAttributeName.ResultCode, 0);
    }

    /**
     * Sets the ResultCode.
     *
     * @param avp - the attribute value
     */
    public void setResultCode(diameter.base.ResultCode avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ResultCode, avp.getData(), true);
    }

    /**
     * Tests whether there is any FinalUnitIndication.
     */
    public boolean containsFinalUnitIndication() {
        return _data.getContainer().contains(DccaAttributeName.FinalUnitIndication);
    }

    /**
     * Gets the FinalUnitIndication.
     */
    public FinalUnitIndication getFinalUnitIndication() throws NoSuchAttributeException {
        return (FinalUnitIndication)_data.getContainer().get(DccaAttributeName.FinalUnitIndication, 0);
    }

    /**
     * Sets the FinalUnitIndication.
     *
     * @param avp - the attribute value
     */
    public void setFinalUnitIndication(FinalUnitIndication avp) {
        _data.getContainer().add(DccaAttributeName.FinalUnitIndication, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsGrantedServiceUnit()) {
            sb.append("    GrantedServiceUnit:");
            try {
                sb.append(getGrantedServiceUnit()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRequestedServiceUnit()) {
            sb.append("    RequestedServiceUnit:");
            try {
                sb.append(getRequestedServiceUnit()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countUsedServiceUnit(); ++i) {
            sb.append("    UsedServiceUnit:");
            try {
                sb.append(getUsedServiceUnit(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTariffChangeUsage()) {
            sb.append("    TariffChangeUsage:");
            try {
                sb.append(getTariffChangeUsage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countServiceIdentifier(); ++i) {
            sb.append("    ServiceIdentifier:");
            try {
                sb.append(getServiceIdentifier(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRatingGroup()) {
            sb.append("    RatingGroup:");
            try {
                sb.append(getRatingGroup()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countGSUPoolReference(); ++i) {
            sb.append("    GSUPoolReference:");
            try {
                sb.append(getGSUPoolReference(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsValidityTime()) {
            sb.append("    ValidityTime:");
            try {
                sb.append(getValidityTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsResultCode()) {
            sb.append("    ResultCode:");
            try {
                sb.append(getResultCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsFinalUnitIndication()) {
            sb.append("    FinalUnitIndication:");
            try {
                sb.append(getFinalUnitIndication()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
