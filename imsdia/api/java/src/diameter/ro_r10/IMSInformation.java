package diameter.ro_r10;

import com.intellinet.diameter.*;


/**
 * IMS-Information AVP is of type Grouped. Its purpose is to allow teh transmission of 
 * additional IMS serrvice specific information elements.
 */
public class IMSInformation extends com.intellinet.diameter.GroupedAVP {
    /**
     * Constructs a new IMSInformation.
     */
    public IMSInformation() {}

    IMSInformation(com.intellinet.diameter.GroupedData data) {
        super(data);
    }

    /**
     * Tests whether there is any EventType.
     */
    public boolean containsEventType() {
        return _data.getContainer().contains(Ro_r10AttributeName.EventType);
    }

    /**
     * Gets the EventType.
     */
    public EventType getEventType() throws NoSuchAttributeException {
        return (EventType)_data.getContainer().get(Ro_r10AttributeName.EventType, 0);
    }

    /**
     * Sets the EventType.
     *
     * @param avp - the attribute value
     */
    public void setEventType(EventType avp) {
        _data.getContainer().add(Ro_r10AttributeName.EventType, avp.getData(), true);
    }

    /**
     * Tests whether there is any RoleOfNode.
     */
    public boolean containsRoleOfNode() {
        return _data.getContainer().contains(Ro_r10AttributeName.RoleOfNode);
    }

    /**
     * Gets the RoleOfNode.
     */
    public RoleOfNode getRoleOfNode() throws NoSuchAttributeException {
        return (RoleOfNode)_data.getContainer().get(Ro_r10AttributeName.RoleOfNode, 0);
    }

    /**
     * Sets the RoleOfNode.
     *
     * @param avp - the attribute value
     */
    public void setRoleOfNode(RoleOfNode avp) {
        _data.getContainer().add(Ro_r10AttributeName.RoleOfNode, avp.getData(), true);
    }

    /**
     * Tests whether there is any NodeFunctionality.
     */
    public boolean containsNodeFunctionality() {
        return _data.getContainer().contains(Ro_r10AttributeName.NodeFunctionality);
    }

    /**
     * Gets the NodeFunctionality.
     */
    public NodeFunctionality getNodeFunctionality() throws NoSuchAttributeException {
        return (NodeFunctionality)_data.getContainer().get(Ro_r10AttributeName.NodeFunctionality, 0);
    }

    /**
     * Sets the NodeFunctionality.
     *
     * @param avp - the attribute value
     */
    public void setNodeFunctionality(NodeFunctionality avp) {
        _data.getContainer().add(Ro_r10AttributeName.NodeFunctionality, avp.getData(), true);
    }

    /**
     * Tests whether there is any UserSessionID.
     */
    public boolean containsUserSessionID() {
        return _data.getContainer().contains(Ro_r10AttributeName.UserSessionID);
    }

    /**
     * Gets the UserSessionID.
     */
    public UserSessionID getUserSessionID() throws NoSuchAttributeException {
        return (UserSessionID)_data.getContainer().get(Ro_r10AttributeName.UserSessionID, 0);
    }

    /**
     * Sets the UserSessionID.
     *
     * @param avp - the attribute value
     */
    public void setUserSessionID(UserSessionID avp) {
        _data.getContainer().add(Ro_r10AttributeName.UserSessionID, avp.getData(), true);
    }

    /**
     * Tests whether there is any OutgoingSessionId.
     */
    public boolean containsOutgoingSessionId() {
        return _data.getContainer().contains(Ro_r10AttributeName.OutgoingSessionId);
    }

    /**
     * Gets the OutgoingSessionId.
     */
    public OutgoingSessionId getOutgoingSessionId() throws NoSuchAttributeException {
        return (OutgoingSessionId)_data.getContainer().get(Ro_r10AttributeName.OutgoingSessionId, 0);
    }

    /**
     * Sets the OutgoingSessionId.
     *
     * @param avp - the attribute value
     */
    public void setOutgoingSessionId(OutgoingSessionId avp) {
        _data.getContainer().add(Ro_r10AttributeName.OutgoingSessionId, avp.getData(), true);
    }

    /**
     * Returns number of CallingPartyAddress instances.
     */
    public int countCallingPartyAddress() {
        return _data.getContainer().count(Ro_r10AttributeName.CallingPartyAddress);
    }

    /**
     * Gets one CallingPartyAddress.
     *
     * @param index - the index of the attribute to return
     */
    public CallingPartyAddress getCallingPartyAddress(int index) throws NoSuchAttributeException {
        return (CallingPartyAddress)_data.getContainer().get(Ro_r10AttributeName.CallingPartyAddress, index);
    }

    /**
     * Adds one CallingPartyAddress.
     *
     * @param avp - the attribute value
     */
    public void addCallingPartyAddress(CallingPartyAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.CallingPartyAddress, avp.getData(), false);
    }

    /**
     * Tests whether there is any SessionPriority.
     */
    public boolean containsSessionPriority() {
        return _data.getContainer().contains(Ro_r10AttributeName.SessionPriority);
    }

    /**
     * Gets the SessionPriority.
     */
    public SessionPriority getSessionPriority() throws NoSuchAttributeException {
        return (SessionPriority)_data.getContainer().get(Ro_r10AttributeName.SessionPriority, 0);
    }

    /**
     * Sets the SessionPriority.
     *
     * @param avp - the attribute value
     */
    public void setSessionPriority(SessionPriority avp) {
        _data.getContainer().add(Ro_r10AttributeName.SessionPriority, avp.getData(), true);
    }

    /**
     * Tests whether there is any CalledPartyAddress.
     */
    public boolean containsCalledPartyAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.CalledPartyAddress);
    }

    /**
     * Gets the CalledPartyAddress.
     */
    public CalledPartyAddress getCalledPartyAddress() throws NoSuchAttributeException {
        return (CalledPartyAddress)_data.getContainer().get(Ro_r10AttributeName.CalledPartyAddress, 0);
    }

    /**
     * Sets the CalledPartyAddress.
     *
     * @param avp - the attribute value
     */
    public void setCalledPartyAddress(CalledPartyAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.CalledPartyAddress, avp.getData(), true);
    }

    /**
     * Returns number of CalledAssertedIdentity instances.
     */
    public int countCalledAssertedIdentity() {
        return _data.getContainer().count(Ro_r10AttributeName.CalledAssertedIdentity);
    }

    /**
     * Gets one CalledAssertedIdentity.
     *
     * @param index - the index of the attribute to return
     */
    public CalledAssertedIdentity getCalledAssertedIdentity(int index) throws NoSuchAttributeException {
        return (CalledAssertedIdentity)_data.getContainer().get(Ro_r10AttributeName.CalledAssertedIdentity, index);
    }

    /**
     * Adds one CalledAssertedIdentity.
     *
     * @param avp - the attribute value
     */
    public void addCalledAssertedIdentity(CalledAssertedIdentity avp) {
        _data.getContainer().add(Ro_r10AttributeName.CalledAssertedIdentity, avp.getData(), false);
    }

    /**
     * Tests whether there is any NumberPortabilityRoutingInformation.
     */
    public boolean containsNumberPortabilityRoutingInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.NumberPortabilityRoutingInformation);
    }

    /**
     * Gets the NumberPortabilityRoutingInformation.
     */
    public NumberPortabilityRoutingInformation getNumberPortabilityRoutingInformation() throws NoSuchAttributeException {
        return (NumberPortabilityRoutingInformation)_data.getContainer().get(Ro_r10AttributeName.NumberPortabilityRoutingInformation, 0);
    }

    /**
     * Sets the NumberPortabilityRoutingInformation.
     *
     * @param avp - the attribute value
     */
    public void setNumberPortabilityRoutingInformation(NumberPortabilityRoutingInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.NumberPortabilityRoutingInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any CarrierSelectRoutingInformation.
     */
    public boolean containsCarrierSelectRoutingInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.CarrierSelectRoutingInformation);
    }

    /**
     * Gets the CarrierSelectRoutingInformation.
     */
    public CarrierSelectRoutingInformation getCarrierSelectRoutingInformation() throws NoSuchAttributeException {
        return (CarrierSelectRoutingInformation)_data.getContainer().get(Ro_r10AttributeName.CarrierSelectRoutingInformation, 0);
    }

    /**
     * Sets the CarrierSelectRoutingInformation.
     *
     * @param avp - the attribute value
     */
    public void setCarrierSelectRoutingInformation(CarrierSelectRoutingInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.CarrierSelectRoutingInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any AlternateChargedPartyAddress.
     */
    public boolean containsAlternateChargedPartyAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.AlternateChargedPartyAddress);
    }

    /**
     * Gets the AlternateChargedPartyAddress.
     */
    public AlternateChargedPartyAddress getAlternateChargedPartyAddress() throws NoSuchAttributeException {
        return (AlternateChargedPartyAddress)_data.getContainer().get(Ro_r10AttributeName.AlternateChargedPartyAddress, 0);
    }

    /**
     * Sets the AlternateChargedPartyAddress.
     *
     * @param avp - the attribute value
     */
    public void setAlternateChargedPartyAddress(AlternateChargedPartyAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.AlternateChargedPartyAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any RequestedPartyAddress.
     */
    public boolean containsRequestedPartyAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.RequestedPartyAddress);
    }

    /**
     * Gets the RequestedPartyAddress.
     */
    public RequestedPartyAddress getRequestedPartyAddress() throws NoSuchAttributeException {
        return (RequestedPartyAddress)_data.getContainer().get(Ro_r10AttributeName.RequestedPartyAddress, 0);
    }

    /**
     * Sets the RequestedPartyAddress.
     *
     * @param avp - the attribute value
     */
    public void setRequestedPartyAddress(RequestedPartyAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.RequestedPartyAddress, avp.getData(), true);
    }

    /**
     * Returns number of AssociatedURI instances.
     */
    public int countAssociatedURI() {
        return _data.getContainer().count(Ro_r10AttributeName.AssociatedURI);
    }

    /**
     * Gets one AssociatedURI.
     *
     * @param index - the index of the attribute to return
     */
    public AssociatedURI getAssociatedURI(int index) throws NoSuchAttributeException {
        return (AssociatedURI)_data.getContainer().get(Ro_r10AttributeName.AssociatedURI, index);
    }

    /**
     * Adds one AssociatedURI.
     *
     * @param avp - the attribute value
     */
    public void addAssociatedURI(AssociatedURI avp) {
        _data.getContainer().add(Ro_r10AttributeName.AssociatedURI, avp.getData(), false);
    }

    /**
     * Tests whether there is any TimeStamps.
     */
    public boolean containsTimeStamps() {
        return _data.getContainer().contains(Ro_r10AttributeName.TimeStamps);
    }

    /**
     * Gets the TimeStamps.
     */
    public TimeStamps getTimeStamps() throws NoSuchAttributeException {
        return (TimeStamps)_data.getContainer().get(Ro_r10AttributeName.TimeStamps, 0);
    }

    /**
     * Sets the TimeStamps.
     *
     * @param avp - the attribute value
     */
    public void setTimeStamps(TimeStamps avp) {
        _data.getContainer().add(Ro_r10AttributeName.TimeStamps, avp.getData(), true);
    }

    /**
     * Returns number of ApplicationServerInformation instances.
     */
    public int countApplicationServerInformation() {
        return _data.getContainer().count(Ro_r10AttributeName.ApplicationServerInformation);
    }

    /**
     * Gets one ApplicationServerInformation.
     *
     * @param index - the index of the attribute to return
     */
    public ApplicationServerInformation getApplicationServerInformation(int index) throws NoSuchAttributeException {
        return (ApplicationServerInformation)_data.getContainer().get(Ro_r10AttributeName.ApplicationServerInformation, index);
    }

    /**
     * Adds one ApplicationServerInformation.
     *
     * @param avp - the attribute value
     */
    public void addApplicationServerInformation(ApplicationServerInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.ApplicationServerInformation, avp.getData(), false);
    }

    /**
     * Returns number of InterOperatorIdentifier instances.
     */
    public int countInterOperatorIdentifier() {
        return _data.getContainer().count(Ro_r10AttributeName.InterOperatorIdentifier);
    }

    /**
     * Gets one InterOperatorIdentifier.
     *
     * @param index - the index of the attribute to return
     */
    public InterOperatorIdentifier getInterOperatorIdentifier(int index) throws NoSuchAttributeException {
        return (InterOperatorIdentifier)_data.getContainer().get(Ro_r10AttributeName.InterOperatorIdentifier, index);
    }

    /**
     * Adds one InterOperatorIdentifier.
     *
     * @param avp - the attribute value
     */
    public void addInterOperatorIdentifier(InterOperatorIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.InterOperatorIdentifier, avp.getData(), false);
    }

    /**
     * Tests whether there is any IMSChargingIdentifier.
     */
    public boolean containsIMSChargingIdentifier() {
        return _data.getContainer().contains(Ro_r10AttributeName.IMSChargingIdentifier);
    }

    /**
     * Gets the IMSChargingIdentifier.
     */
    public IMSChargingIdentifier getIMSChargingIdentifier() throws NoSuchAttributeException {
        return (IMSChargingIdentifier)_data.getContainer().get(Ro_r10AttributeName.IMSChargingIdentifier, 0);
    }

    /**
     * Sets the IMSChargingIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setIMSChargingIdentifier(IMSChargingIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.IMSChargingIdentifier, avp.getData(), true);
    }

    /**
     * Returns number of SDPSessionDescription instances.
     */
    public int countSDPSessionDescription() {
        return _data.getContainer().count(Ro_r10AttributeName.SDPSessionDescription);
    }

    /**
     * Gets one SDPSessionDescription.
     *
     * @param index - the index of the attribute to return
     */
    public SDPSessionDescription getSDPSessionDescription(int index) throws NoSuchAttributeException {
        return (SDPSessionDescription)_data.getContainer().get(Ro_r10AttributeName.SDPSessionDescription, index);
    }

    /**
     * Adds one SDPSessionDescription.
     *
     * @param avp - the attribute value
     */
    public void addSDPSessionDescription(SDPSessionDescription avp) {
        _data.getContainer().add(Ro_r10AttributeName.SDPSessionDescription, avp.getData(), false);
    }

    /**
     * Returns number of SDPMediaComponent instances.
     */
    public int countSDPMediaComponent() {
        return _data.getContainer().count(Ro_r10AttributeName.SDPMediaComponent);
    }

    /**
     * Gets one SDPMediaComponent.
     *
     * @param index - the index of the attribute to return
     */
    public SDPMediaComponent getSDPMediaComponent(int index) throws NoSuchAttributeException {
        return (SDPMediaComponent)_data.getContainer().get(Ro_r10AttributeName.SDPMediaComponent, index);
    }

    /**
     * Adds one SDPMediaComponent.
     *
     * @param avp - the attribute value
     */
    public void addSDPMediaComponent(SDPMediaComponent avp) {
        _data.getContainer().add(Ro_r10AttributeName.SDPMediaComponent, avp.getData(), false);
    }

    /**
     * Tests whether there is any ServedPartyIPAddress.
     */
    public boolean containsServedPartyIPAddress() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServedPartyIPAddress);
    }

    /**
     * Gets the ServedPartyIPAddress.
     */
    public ServedPartyIPAddress getServedPartyIPAddress() throws NoSuchAttributeException {
        return (ServedPartyIPAddress)_data.getContainer().get(Ro_r10AttributeName.ServedPartyIPAddress, 0);
    }

    /**
     * Sets the ServedPartyIPAddress.
     *
     * @param avp - the attribute value
     */
    public void setServedPartyIPAddress(ServedPartyIPAddress avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServedPartyIPAddress, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServerCapabilities.
     */
    public boolean containsServerCapabilities() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServerCapabilities);
    }

    /**
     * Gets the ServerCapabilities.
     */
    public ServerCapabilities getServerCapabilities() throws NoSuchAttributeException {
        return (ServerCapabilities)_data.getContainer().get(Ro_r10AttributeName.ServerCapabilities, 0);
    }

    /**
     * Sets the ServerCapabilities.
     *
     * @param avp - the attribute value
     */
    public void setServerCapabilities(ServerCapabilities avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServerCapabilities, avp.getData(), true);
    }

    /**
     * Tests whether there is any TrunkGroupID.
     */
    public boolean containsTrunkGroupID() {
        return _data.getContainer().contains(Ro_r10AttributeName.TrunkGroupID);
    }

    /**
     * Gets the TrunkGroupID.
     */
    public TrunkGroupID getTrunkGroupID() throws NoSuchAttributeException {
        return (TrunkGroupID)_data.getContainer().get(Ro_r10AttributeName.TrunkGroupID, 0);
    }

    /**
     * Sets the TrunkGroupID.
     *
     * @param avp - the attribute value
     */
    public void setTrunkGroupID(TrunkGroupID avp) {
        _data.getContainer().add(Ro_r10AttributeName.TrunkGroupID, avp.getData(), true);
    }

    /**
     * Tests whether there is any BearerService.
     */
    public boolean containsBearerService() {
        return _data.getContainer().contains(Ro_r10AttributeName.BearerService);
    }

    /**
     * Gets the BearerService.
     */
    public BearerService getBearerService() throws NoSuchAttributeException {
        return (BearerService)_data.getContainer().get(Ro_r10AttributeName.BearerService, 0);
    }

    /**
     * Sets the BearerService.
     *
     * @param avp - the attribute value
     */
    public void setBearerService(BearerService avp) {
        _data.getContainer().add(Ro_r10AttributeName.BearerService, avp.getData(), true);
    }

    /**
     * Tests whether there is any ServiceId.
     */
    public boolean containsServiceId() {
        return _data.getContainer().contains(Ro_r10AttributeName.ServiceId);
    }

    /**
     * Gets the ServiceId.
     */
    public ServiceId getServiceId() throws NoSuchAttributeException {
        return (ServiceId)_data.getContainer().get(Ro_r10AttributeName.ServiceId, 0);
    }

    /**
     * Sets the ServiceId.
     *
     * @param avp - the attribute value
     */
    public void setServiceId(ServiceId avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceId, avp.getData(), true);
    }

    /**
     * Returns number of ServiceSpecificInfo instances.
     */
    public int countServiceSpecificInfo() {
        return _data.getContainer().count(Ro_r10AttributeName.ServiceSpecificInfo);
    }

    /**
     * Gets one ServiceSpecificInfo.
     *
     * @param index - the index of the attribute to return
     */
    public ServiceSpecificInfo getServiceSpecificInfo(int index) throws NoSuchAttributeException {
        return (ServiceSpecificInfo)_data.getContainer().get(Ro_r10AttributeName.ServiceSpecificInfo, index);
    }

    /**
     * Adds one ServiceSpecificInfo.
     *
     * @param avp - the attribute value
     */
    public void addServiceSpecificInfo(ServiceSpecificInfo avp) {
        _data.getContainer().add(Ro_r10AttributeName.ServiceSpecificInfo, avp.getData(), false);
    }

    /**
     * Returns number of MessageBody instances.
     */
    public int countMessageBody() {
        return _data.getContainer().count(Ro_r10AttributeName.MessageBody);
    }

    /**
     * Gets one MessageBody.
     *
     * @param index - the index of the attribute to return
     */
    public MessageBody getMessageBody(int index) throws NoSuchAttributeException {
        return (MessageBody)_data.getContainer().get(Ro_r10AttributeName.MessageBody, index);
    }

    /**
     * Adds one MessageBody.
     *
     * @param avp - the attribute value
     */
    public void addMessageBody(MessageBody avp) {
        _data.getContainer().add(Ro_r10AttributeName.MessageBody, avp.getData(), false);
    }

    /**
     * Tests whether there is any CauseCode.
     */
    public boolean containsCauseCode() {
        return _data.getContainer().contains(Ro_r10AttributeName.CauseCode);
    }

    /**
     * Gets the CauseCode.
     */
    public CauseCode getCauseCode() throws NoSuchAttributeException {
        return (CauseCode)_data.getContainer().get(Ro_r10AttributeName.CauseCode, 0);
    }

    /**
     * Sets the CauseCode.
     *
     * @param avp - the attribute value
     */
    public void setCauseCode(CauseCode avp) {
        _data.getContainer().add(Ro_r10AttributeName.CauseCode, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccessNetworkInformation.
     */
    public boolean containsAccessNetworkInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.AccessNetworkInformation);
    }

    /**
     * Gets the AccessNetworkInformation.
     */
    public AccessNetworkInformation getAccessNetworkInformation() throws NoSuchAttributeException {
        return (AccessNetworkInformation)_data.getContainer().get(Ro_r10AttributeName.AccessNetworkInformation, 0);
    }

    /**
     * Sets the AccessNetworkInformation.
     *
     * @param avp - the attribute value
     */
    public void setAccessNetworkInformation(AccessNetworkInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.AccessNetworkInformation, avp.getData(), true);
    }

    /**
     * Returns number of EarlyMediaDescription instances.
     */
    public int countEarlyMediaDescription() {
        return _data.getContainer().count(Ro_r10AttributeName.EarlyMediaDescription);
    }

    /**
     * Gets one EarlyMediaDescription.
     *
     * @param index - the index of the attribute to return
     */
    public EarlyMediaDescription getEarlyMediaDescription(int index) throws NoSuchAttributeException {
        return (EarlyMediaDescription)_data.getContainer().get(Ro_r10AttributeName.EarlyMediaDescription, index);
    }

    /**
     * Adds one EarlyMediaDescription.
     *
     * @param avp - the attribute value
     */
    public void addEarlyMediaDescription(EarlyMediaDescription avp) {
        _data.getContainer().add(Ro_r10AttributeName.EarlyMediaDescription, avp.getData(), false);
    }

    /**
     * Tests whether there is any IMSCommunicationServiceIdentifier.
     */
    public boolean containsIMSCommunicationServiceIdentifier() {
        return _data.getContainer().contains(Ro_r10AttributeName.IMSCommunicationServiceIdentifier);
    }

    /**
     * Gets the IMSCommunicationServiceIdentifier.
     */
    public IMSCommunicationServiceIdentifier getIMSCommunicationServiceIdentifier() throws NoSuchAttributeException {
        return (IMSCommunicationServiceIdentifier)_data.getContainer().get(Ro_r10AttributeName.IMSCommunicationServiceIdentifier, 0);
    }

    /**
     * Sets the IMSCommunicationServiceIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setIMSCommunicationServiceIdentifier(IMSCommunicationServiceIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.IMSCommunicationServiceIdentifier, avp.getData(), true);
    }

    /**
     * Tests whether there is any OnlineChargingFlag.
     */
    public boolean containsOnlineChargingFlag() {
        return _data.getContainer().contains(Ro_r10AttributeName.OnlineChargingFlag);
    }

    /**
     * Gets the OnlineChargingFlag.
     */
    public OnlineChargingFlag getOnlineChargingFlag() throws NoSuchAttributeException {
        return (OnlineChargingFlag)_data.getContainer().get(Ro_r10AttributeName.OnlineChargingFlag, 0);
    }

    /**
     * Sets the OnlineChargingFlag.
     *
     * @param avp - the attribute value
     */
    public void setOnlineChargingFlag(OnlineChargingFlag avp) {
        _data.getContainer().add(Ro_r10AttributeName.OnlineChargingFlag, avp.getData(), true);
    }

    /**
     * Tests whether there is any RealTimeTariffInformation.
     */
    public boolean containsRealTimeTariffInformation() {
        return _data.getContainer().contains(Ro_r10AttributeName.RealTimeTariffInformation);
    }

    /**
     * Gets the RealTimeTariffInformation.
     */
    public RealTimeTariffInformation getRealTimeTariffInformation() throws NoSuchAttributeException {
        return (RealTimeTariffInformation)_data.getContainer().get(Ro_r10AttributeName.RealTimeTariffInformation, 0);
    }

    /**
     * Sets the RealTimeTariffInformation.
     *
     * @param avp - the attribute value
     */
    public void setRealTimeTariffInformation(RealTimeTariffInformation avp) {
        _data.getContainer().add(Ro_r10AttributeName.RealTimeTariffInformation, avp.getData(), true);
    }

    /**
     * Tests whether there is any AccountExpiration.
     */
    public boolean containsAccountExpiration() {
        return _data.getContainer().contains(Ro_r10AttributeName.AccountExpiration);
    }

    /**
     * Gets the AccountExpiration.
     */
    public AccountExpiration getAccountExpiration() throws NoSuchAttributeException {
        return (AccountExpiration)_data.getContainer().get(Ro_r10AttributeName.AccountExpiration, 0);
    }

    /**
     * Sets the AccountExpiration.
     *
     * @param avp - the attribute value
     */
    public void setAccountExpiration(AccountExpiration avp) {
        _data.getContainer().add(Ro_r10AttributeName.AccountExpiration, avp.getData(), true);
    }

    /**
     * Tests whether there is any InitialIMSChargingIdentifier.
     */
    public boolean containsInitialIMSChargingIdentifier() {
        return _data.getContainer().contains(Ro_r10AttributeName.InitialIMSChargingIdentifier);
    }

    /**
     * Gets the InitialIMSChargingIdentifier.
     */
    public InitialIMSChargingIdentifier getInitialIMSChargingIdentifier() throws NoSuchAttributeException {
        return (InitialIMSChargingIdentifier)_data.getContainer().get(Ro_r10AttributeName.InitialIMSChargingIdentifier, 0);
    }

    /**
     * Sets the InitialIMSChargingIdentifier.
     *
     * @param avp - the attribute value
     */
    public void setInitialIMSChargingIdentifier(InitialIMSChargingIdentifier avp) {
        _data.getContainer().add(Ro_r10AttributeName.InitialIMSChargingIdentifier, avp.getData(), true);
    }


    public String toString() {
        StringBuffer sb = new StringBuffer(" {\n");
        if (containsEventType()) {
            sb.append("    EventType:");
            try {
                sb.append(getEventType()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRoleOfNode()) {
            sb.append("    RoleOfNode:");
            try {
                sb.append(getRoleOfNode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNodeFunctionality()) {
            sb.append("    NodeFunctionality:");
            try {
                sb.append(getNodeFunctionality()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsUserSessionID()) {
            sb.append("    UserSessionID:");
            try {
                sb.append(getUserSessionID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOutgoingSessionId()) {
            sb.append("    OutgoingSessionId:");
            try {
                sb.append(getOutgoingSessionId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countCallingPartyAddress(); ++i) {
            sb.append("    CallingPartyAddress:");
            try {
                sb.append(getCallingPartyAddress(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsSessionPriority()) {
            sb.append("    SessionPriority:");
            try {
                sb.append(getSessionPriority()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCalledPartyAddress()) {
            sb.append("    CalledPartyAddress:");
            try {
                sb.append(getCalledPartyAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countCalledAssertedIdentity(); ++i) {
            sb.append("    CalledAssertedIdentity:");
            try {
                sb.append(getCalledAssertedIdentity(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsNumberPortabilityRoutingInformation()) {
            sb.append("    NumberPortabilityRoutingInformation:");
            try {
                sb.append(getNumberPortabilityRoutingInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCarrierSelectRoutingInformation()) {
            sb.append("    CarrierSelectRoutingInformation:");
            try {
                sb.append(getCarrierSelectRoutingInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAlternateChargedPartyAddress()) {
            sb.append("    AlternateChargedPartyAddress:");
            try {
                sb.append(getAlternateChargedPartyAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRequestedPartyAddress()) {
            sb.append("    RequestedPartyAddress:");
            try {
                sb.append(getRequestedPartyAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countAssociatedURI(); ++i) {
            sb.append("    AssociatedURI:");
            try {
                sb.append(getAssociatedURI(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTimeStamps()) {
            sb.append("    TimeStamps:");
            try {
                sb.append(getTimeStamps()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countApplicationServerInformation(); ++i) {
            sb.append("    ApplicationServerInformation:");
            try {
                sb.append(getApplicationServerInformation(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countInterOperatorIdentifier(); ++i) {
            sb.append("    InterOperatorIdentifier:");
            try {
                sb.append(getInterOperatorIdentifier(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIMSChargingIdentifier()) {
            sb.append("    IMSChargingIdentifier:");
            try {
                sb.append(getIMSChargingIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSDPSessionDescription(); ++i) {
            sb.append("    SDPSessionDescription:");
            try {
                sb.append(getSDPSessionDescription(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countSDPMediaComponent(); ++i) {
            sb.append("    SDPMediaComponent:");
            try {
                sb.append(getSDPMediaComponent(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServedPartyIPAddress()) {
            sb.append("    ServedPartyIPAddress:");
            try {
                sb.append(getServedPartyIPAddress()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServerCapabilities()) {
            sb.append("    ServerCapabilities:");
            try {
                sb.append(getServerCapabilities()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsTrunkGroupID()) {
            sb.append("    TrunkGroupID:");
            try {
                sb.append(getTrunkGroupID()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsBearerService()) {
            sb.append("    BearerService:");
            try {
                sb.append(getBearerService()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsServiceId()) {
            sb.append("    ServiceId:");
            try {
                sb.append(getServiceId()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countServiceSpecificInfo(); ++i) {
            sb.append("    ServiceSpecificInfo:");
            try {
                sb.append(getServiceSpecificInfo(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countMessageBody(); ++i) {
            sb.append("    MessageBody:");
            try {
                sb.append(getMessageBody(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsCauseCode()) {
            sb.append("    CauseCode:");
            try {
                sb.append(getCauseCode()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccessNetworkInformation()) {
            sb.append("    AccessNetworkInformation:");
            try {
                sb.append(getAccessNetworkInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        for (int i = 0; i < countEarlyMediaDescription(); ++i) {
            sb.append("    EarlyMediaDescription:");
            try {
                sb.append(getEarlyMediaDescription(i)).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsIMSCommunicationServiceIdentifier()) {
            sb.append("    IMSCommunicationServiceIdentifier:");
            try {
                sb.append(getIMSCommunicationServiceIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsOnlineChargingFlag()) {
            sb.append("    OnlineChargingFlag:");
            try {
                sb.append(getOnlineChargingFlag()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsRealTimeTariffInformation()) {
            sb.append("    RealTimeTariffInformation:");
            try {
                sb.append(getRealTimeTariffInformation()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsAccountExpiration()) {
            sb.append("    AccountExpiration:");
            try {
                sb.append(getAccountExpiration()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        if (containsInitialIMSChargingIdentifier()) {
            sb.append("    InitialIMSChargingIdentifier:");
            try {
                sb.append(getInitialIMSChargingIdentifier()).append('\n');
            } catch (NoSuchAttributeException x) {
                sb.append("[said present but missing]\n");
            }
        }
        return sb.append('}').toString();
    }
}
