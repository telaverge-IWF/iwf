package diameter.dcca;

import com.intellinet.diameter.*;


public class CreditControlAnswer extends com.intellinet.diameter.Command {
    /**
     * Constructs a new CreditControlAnswer command.
     *
     * @param error - whether this command carries an error indicator
     * @param retrans - whether this is a retransmission
     */
    public CreditControlAnswer(boolean error, boolean retrans) {
        super(false, true, error, retrans, 272, 4);
    }

    /**
     * Constructs a CreditControlAnswer command by decoding a byte array.
     *
     * @param buffer - the buffer that contains the encoded bytes
     */
    public CreditControlAnswer(byte[] buffer) throws WrongCommandTypeException, CodecException {
        super(buffer);
        validate();
    }

    /**
     * Constructs a CreditControlAnswer command from a GenericCommand.
     *
     * @param generic - the GenericCommand
     */
    public CreditControlAnswer(GenericCommand generic) throws WrongCommandTypeException {
        super(generic.transfer());
        validate();
    }

    CreditControlAnswer(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {
        super(data);
        validate();
    }

    /**
     * Gets the SessionId.
     */
    public diameter.base.SessionId getSessionId() throws NoSuchAttributeException {
        return (diameter.base.SessionId)_data.getContainer().get(diameter.base.BaseAttributeName.SessionId, 0);
    }

    /**
     * Sets the SessionId.
     *
     * @param avp - the attribute value
     */
    public void setSessionId(diameter.base.SessionId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.SessionId, avp.getData(), true);
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
     * Gets the OriginHost.
     */
    public diameter.base.OriginHost getOriginHost() throws NoSuchAttributeException {
        return (diameter.base.OriginHost)_data.getContainer().get(diameter.base.BaseAttributeName.OriginHost, 0);
    }

    /**
     * Sets the OriginHost.
     *
     * @param avp - the attribute value
     */
    public void setOriginHost(diameter.base.OriginHost avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.OriginHost, avp.getData(), true);
    }

    /**
     * Gets the OriginRealm.
     */
    public diameter.base.OriginRealm getOriginRealm() throws NoSuchAttributeException {
        return (diameter.base.OriginRealm)_data.getContainer().get(diameter.base.BaseAttributeName.OriginRealm, 0);
    }

    /**
     * Sets the OriginRealm.
     *
     * @param avp - the attribute value
     */
    public void setOriginRealm(diameter.base.OriginRealm avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.OriginRealm, avp.getData(), true);
    }

    /**
     * Gets the AuthApplicationId.
     */
    public diameter.base.AuthApplicationId getAuthApplicationId() throws NoSuchAttributeException {
        return (diameter.base.AuthApplicationId)_data.getContainer().get(diameter.base.BaseAttributeName.AuthApplicationId, 0);
    }

    /**
     * Sets the AuthApplicationId.
     *
     * @param avp - the attribute value
     */
    public void setAuthApplicationId(diameter.base.AuthApplicationId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AuthApplicationId, avp.getData(), true);
    }

    /**
     * Gets the CCRequestType.
     */
    public CCRequestType getCCRequestType() throws NoSuchAttributeException {
        return (CCRequestType)_data.getContainer().get(DccaAttributeName.CCRequestType, 0);
    }

    /**
     * Sets the CCRequestType.
     *
     * @param avp - the attribute value
     */
    public void setCCRequestType(CCRequestType avp) {
        _data.getContainer().add(DccaAttributeName.CCRequestType, avp.getData(), true);
    }

    /**
     * Gets the CCRequestNumber.
     */
    public CCRequestNumber getCCRequestNumber() throws NoSuchAttributeException {
        return (CCRequestNumber)_data.getContainer().get(DccaAttributeName.CCRequestNumber, 0);
    }

    /**
     * Sets the CCRequestNumber.
     *
     * @param avp - the attribute value
     */
    public void setCCRequestNumber(CCRequestNumber avp) {
        _data.getContainer().add(DccaAttributeName.CCRequestNumber, avp.getData(), true);
    }

    /**
     * Tests whether there is any UserName.
     */
    public boolean containsUserName() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.UserName);
    }

    /**
     * Gets the UserName.
     */
    public diameter.base.UserName getUserName() throws NoSuchAttributeException {
        return (diameter.base.UserName)_data.getContainer().get(diameter.base.BaseAttributeName.UserName, 0);
    }

    /**
     * Sets the UserName.
     *
     * @param avp - the attribute value
     */
    public void setUserName(diameter.base.UserName avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.UserName, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCSessionFailover.
     */
    public boolean containsCCSessionFailover() {
        return _data.getContainer().contains(DccaAttributeName.CCSessionFailover);
    }

    /**
     * Gets the CCSessionFailover.
     */
    public CCSessionFailover getCCSessionFailover() throws NoSuchAttributeException {
        return (CCSessionFailover)_data.getContainer().get(DccaAttributeName.CCSessionFailover, 0);
    }

    /**
     * Sets the CCSessionFailover.
     *
     * @param avp - the attribute value
     */
    public void setCCSessionFailover(CCSessionFailover avp) {
        _data.getContainer().add(DccaAttributeName.CCSessionFailover, avp.getData(), true);
    }

    /**
     * Tests whether there is any CCSubSessionId.
     */
    public boolean containsCCSubSessionId() {
        return _data.getContainer().contains(DccaAttributeName.CCSubSessionId);
    }

    /**
     * Gets the CCSubSessionId.
     */
    public CCSubSessionId getCCSubSessionId() throws NoSuchAttributeException {
        return (CCSubSessionId)_data.getContainer().get(DccaAttributeName.CCSubSessionId, 0);
    }

    /**
     * Sets the CCSubSessionId.
     *
     * @param avp - the attribute value
     */
    public void setCCSubSessionId(CCSubSessionId avp) {
        _data.getContainer().add(DccaAttributeName.CCSubSessionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any AcctMultiSessionId.
     */
    public boolean containsAcctMultiSessionId() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.AcctMultiSessionId);
    }

    /**
     * Gets the AcctMultiSessionId.
     */
    public diameter.base.AcctMultiSessionId getAcctMultiSessionId() throws NoSuchAttributeException {
        return (diameter.base.AcctMultiSessionId)_data.getContainer().get(diameter.base.BaseAttributeName.AcctMultiSessionId, 0);
    }

    /**
     * Sets the AcctMultiSessionId.
     *
     * @param avp - the attribute value
     */
    public void setAcctMultiSessionId(diameter.base.AcctMultiSessionId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.AcctMultiSessionId, avp.getData(), true);
    }

    /**
     * Tests whether there is any OriginStateId.
     */
    public boolean containsOriginStateId() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.OriginStateId);
    }

    /**
     * Gets the OriginStateId.
     */
    public diameter.base.OriginStateId getOriginStateId() throws NoSuchAttributeException {
        return (diameter.base.OriginStateId)_data.getContainer().get(diameter.base.BaseAttributeName.OriginStateId, 0);
    }

    /**
     * Sets the OriginStateId.
     *
     * @param avp - the attribute value
     */
    public void setOriginStateId(diameter.base.OriginStateId avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.OriginStateId, avp.getData(), true);
    }

    /**
     * Tests whether there is any EventTimestamp.
     */
    public boolean containsEventTimestamp() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.EventTimestamp);
    }

    /**
     * Gets the EventTimestamp.
     */
    public diameter.base.EventTimestamp getEventTimestamp() throws NoSuchAttributeException {
        return (diameter.base.EventTimestamp)_data.getContainer().get(diameter.base.BaseAttributeName.EventTimestamp, 0);
    }

    /**
     * Sets the EventTimestamp.
     *
     * @param avp - the attribute value
     */
    public void setEventTimestamp(diameter.base.EventTimestamp avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.EventTimestamp, avp.getData(), true);
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
     * Returns number of MultipleServicesCreditControl instances.
     */
    public int countMultipleServicesCreditControl() {
        return _data.getContainer().count(DccaAttributeName.MultipleServicesCreditControl);
    }

    /**
     * Gets one MultipleServicesCreditControl.
     *
     * @param index - the index of the attribute to return
     */
    public MultipleServicesCreditControl getMultipleServicesCreditControl(int index) throws NoSuchAttributeException {
        return (MultipleServicesCreditControl)_data.getContainer().get(DccaAttributeName.MultipleServicesCreditControl, index);
    }

    /**
     * Adds one MultipleServicesCreditControl.
     *
     * @param avp - the attribute value
     */
    public void addMultipleServicesCreditControl(MultipleServicesCreditControl avp) {
        _data.getContainer().add(DccaAttributeName.MultipleServicesCreditControl, avp.getData(), false);
    }

    /**
     * Tests whether there is any CostInformation.
     */
    public boolean containsCostInformation() {
        return _data.getContainer().contains(DccaAttributeName.CostInformation);
    }

    /**
     * Gets the CostInformation.
     */
    public CostInformation getCostInformation() throws NoSuchAttributeException {
        return (CostInformation)_data.getContainer().get(DccaAttributeName.CostInformation, 0);
    }

    /**
     * Sets the CostInformation.
     *
     * @param avp - the attribute value
     */
    public void setCostInformation(CostInformation avp) {
        _data.getContainer().add(DccaAttributeName.CostInformation, avp.getData(), true);
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

    /**
     * Tests whether there is any CheckBalanceResult.
     */
    public boolean containsCheckBalanceResult() {
        return _data.getContainer().contains(DccaAttributeName.CheckBalanceResult);
    }

    /**
     * Gets the CheckBalanceResult.
     */
    public CheckBalanceResult getCheckBalanceResult() throws NoSuchAttributeException {
        return (CheckBalanceResult)_data.getContainer().get(DccaAttributeName.CheckBalanceResult, 0);
    }

    /**
     * Sets the CheckBalanceResult.
     *
     * @param avp - the attribute value
     */
    public void setCheckBalanceResult(CheckBalanceResult avp) {
        _data.getContainer().add(DccaAttributeName.CheckBalanceResult, avp.getData(), true);
    }

    /**
     * Tests whether there is any CreditControlFailureHandling.
     */
    public boolean containsCreditControlFailureHandling() {
        return _data.getContainer().contains(DccaAttributeName.CreditControlFailureHandling);
    }

    /**
     * Gets the CreditControlFailureHandling.
     */
    public CreditControlFailureHandling getCreditControlFailureHandling() throws NoSuchAttributeException {
        return (CreditControlFailureHandling)_data.getContainer().get(DccaAttributeName.CreditControlFailureHandling, 0);
    }

    /**
     * Sets the CreditControlFailureHandling.
     *
     * @param avp - the attribute value
     */
    public void setCreditControlFailureHandling(CreditControlFailureHandling avp) {
        _data.getContainer().add(DccaAttributeName.CreditControlFailureHandling, avp.getData(), true);
    }

    /**
     * Tests whether there is any DirectDebitingFailureHandling.
     */
    public boolean containsDirectDebitingFailureHandling() {
        return _data.getContainer().contains(DccaAttributeName.DirectDebitingFailureHandling);
    }

    /**
     * Gets the DirectDebitingFailureHandling.
     */
    public DirectDebitingFailureHandling getDirectDebitingFailureHandling() throws NoSuchAttributeException {
        return (DirectDebitingFailureHandling)_data.getContainer().get(DccaAttributeName.DirectDebitingFailureHandling, 0);
    }

    /**
     * Sets the DirectDebitingFailureHandling.
     *
     * @param avp - the attribute value
     */
    public void setDirectDebitingFailureHandling(DirectDebitingFailureHandling avp) {
        _data.getContainer().add(DccaAttributeName.DirectDebitingFailureHandling, avp.getData(), true);
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
     * Returns number of RedirectHost instances.
     */
    public int countRedirectHost() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.RedirectHost);
    }

    /**
     * Gets one RedirectHost.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.RedirectHost getRedirectHost(int index) throws NoSuchAttributeException {
        return (diameter.base.RedirectHost)_data.getContainer().get(diameter.base.BaseAttributeName.RedirectHost, index);
    }

    /**
     * Adds one RedirectHost.
     *
     * @param avp - the attribute value
     */
    public void addRedirectHost(diameter.base.RedirectHost avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.RedirectHost, avp.getData(), false);
    }

    /**
     * Tests whether there is any RedirectHostUsage.
     */
    public boolean containsRedirectHostUsage() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.RedirectHostUsage);
    }

    /**
     * Gets the RedirectHostUsage.
     */
    public diameter.base.RedirectHostUsage getRedirectHostUsage() throws NoSuchAttributeException {
        return (diameter.base.RedirectHostUsage)_data.getContainer().get(diameter.base.BaseAttributeName.RedirectHostUsage, 0);
    }

    /**
     * Sets the RedirectHostUsage.
     *
     * @param avp - the attribute value
     */
    public void setRedirectHostUsage(diameter.base.RedirectHostUsage avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.RedirectHostUsage, avp.getData(), true);
    }

    /**
     * Tests whether there is any RedirectMaxCacheTime.
     */
    public boolean containsRedirectMaxCacheTime() {
        return _data.getContainer().contains(diameter.base.BaseAttributeName.RedirectMaxCacheTime);
    }

    /**
     * Gets the RedirectMaxCacheTime.
     */
    public diameter.base.RedirectMaxCacheTime getRedirectMaxCacheTime() throws NoSuchAttributeException {
        return (diameter.base.RedirectMaxCacheTime)_data.getContainer().get(diameter.base.BaseAttributeName.RedirectMaxCacheTime, 0);
    }

    /**
     * Sets the RedirectMaxCacheTime.
     *
     * @param avp - the attribute value
     */
    public void setRedirectMaxCacheTime(diameter.base.RedirectMaxCacheTime avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.RedirectMaxCacheTime, avp.getData(), true);
    }

    /**
     * Returns number of ProxyInfo instances.
     */
    public int countProxyInfo() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.ProxyInfo);
    }

    /**
     * Gets one ProxyInfo.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.ProxyInfo getProxyInfo(int index) throws NoSuchAttributeException {
        return (diameter.base.ProxyInfo)_data.getContainer().get(diameter.base.BaseAttributeName.ProxyInfo, index);
    }

    /**
     * Adds one ProxyInfo.
     *
     * @param avp - the attribute value
     */
    public void addProxyInfo(diameter.base.ProxyInfo avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.ProxyInfo, avp.getData(), false);
    }

    /**
     * Returns number of RouteRecord instances.
     */
    public int countRouteRecord() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.RouteRecord);
    }

    /**
     * Gets one RouteRecord.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.RouteRecord getRouteRecord(int index) throws NoSuchAttributeException {
        return (diameter.base.RouteRecord)_data.getContainer().get(diameter.base.BaseAttributeName.RouteRecord, index);
    }

    /**
     * Adds one RouteRecord.
     *
     * @param avp - the attribute value
     */
    public void addRouteRecord(diameter.base.RouteRecord avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.RouteRecord, avp.getData(), false);
    }

    /**
     * Returns number of FailedAVP instances.
     */
    public int countFailedAVP() {
        return _data.getContainer().count(diameter.base.BaseAttributeName.FailedAVP);
    }

    /**
     * Gets one FailedAVP.
     *
     * @param index - the index of the attribute to return
     */
    public diameter.base.FailedAVP getFailedAVP(int index) throws NoSuchAttributeException {
        return (diameter.base.FailedAVP)_data.getContainer().get(diameter.base.BaseAttributeName.FailedAVP, index);
    }

    /**
     * Adds one FailedAVP.
     *
     * @param avp - the attribute value
     */
    public void addFailedAVP(diameter.base.FailedAVP avp) {
        _data.getContainer().add(diameter.base.BaseAttributeName.FailedAVP, avp.getData(), false);
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
        StringBuffer sb = headerToStringBuffer().append(" {\n");
        sb.append("    SessionId:");
            try {
                sb.append(getSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[fixed but missing]\n");
            }
        sb.append("    ResultCode:");
            try {
                sb.append(getResultCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    OriginHost:");
            try {
                sb.append(getOriginHost()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    OriginRealm:");
            try {
                sb.append(getOriginRealm()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    AuthApplicationId:");
            try {
                sb.append(getAuthApplicationId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    CCRequestType:");
            try {
                sb.append(getCCRequestType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        sb.append("    CCRequestNumber:");
            try {
                sb.append(getCCRequestNumber()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[required but missing]\n");
            }
        if (containsUserName()) {
            sb.append("    UserName:");
            try {
                sb.append(getUserName()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCSessionFailover()) {
            sb.append("    CCSessionFailover:");
            try {
                sb.append(getCCSessionFailover()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCCSubSessionId()) {
            sb.append("    CCSubSessionId:");
            try {
                sb.append(getCCSubSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAcctMultiSessionId()) {
            sb.append("    AcctMultiSessionId:");
            try {
                sb.append(getAcctMultiSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOriginStateId()) {
            sb.append("    OriginStateId:");
            try {
                sb.append(getOriginStateId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsEventTimestamp()) {
            sb.append("    EventTimestamp:");
            try {
                sb.append(getEventTimestamp()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsGrantedServiceUnit()) {
            sb.append("    GrantedServiceUnit:");
            try {
                sb.append(getGrantedServiceUnit()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countMultipleServicesCreditControl(); ++i) {
            sb.append("    MultipleServicesCreditControl:");
            try {
                sb.append(getMultipleServicesCreditControl(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCostInformation()) {
            sb.append("    CostInformation:");
            try {
                sb.append(getCostInformation()).append('\n');
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
        if (containsCheckBalanceResult()) {
            sb.append("    CheckBalanceResult:");
            try {
                sb.append(getCheckBalanceResult()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCreditControlFailureHandling()) {
            sb.append("    CreditControlFailureHandling:");
            try {
                sb.append(getCreditControlFailureHandling()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsDirectDebitingFailureHandling()) {
            sb.append("    DirectDebitingFailureHandling:");
            try {
                sb.append(getDirectDebitingFailureHandling()).append('\n');
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
        for (int i = 0; i < countRedirectHost(); ++i) {
            sb.append("    RedirectHost:");
            try {
                sb.append(getRedirectHost(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRedirectHostUsage()) {
            sb.append("    RedirectHostUsage:");
            try {
                sb.append(getRedirectHostUsage()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRedirectMaxCacheTime()) {
            sb.append("    RedirectMaxCacheTime:");
            try {
                sb.append(getRedirectMaxCacheTime()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countProxyInfo(); ++i) {
            sb.append("    ProxyInfo:");
            try {
                sb.append(getProxyInfo(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countRouteRecord(); ++i) {
            sb.append("    RouteRecord:");
            try {
                sb.append(getRouteRecord(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countFailedAVP(); ++i) {
            sb.append("    FailedAVP:");
            try {
                sb.append(getFailedAVP(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        sb.append("    ANY:").append(_data.getContainer().extrasToString()).append('\n');
        return sb.append('}').toString();
    }

    private void validate() throws WrongCommandTypeException {
        if (getCommandCode() != 272 || isRequest()) {
            throw new WrongCommandTypeException(getCommandName());
        }
    }
}
