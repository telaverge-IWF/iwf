package com.intellinet.diameter.mag;

import java.util.*;
import com.intellinet.diameter.mag.analysis.DepthFirstAdapter;
import com.intellinet.diameter.mag.node.*;
import com.intellinet.diameter.mag.util.*;


/**
 * This analyzer performs semantic checking on the protocol specification.
 *
 * <ol>
 * <li> Validate uniqueness of AVP names and codes
 * <li> Validate all enumerated and grouped AVP definitions
 * <li> Validate all references to AVP names in grouped AVP and command definitions
 * </ol>
 */
public class SemanticAnalyzer extends DepthFirstAdapter {
    //private final List<SemanticAnalyzer> _known;
    private final SemanticAnalyzer _parent;
    private boolean _passed = true;
    private AGrammar _grammar;
    private Map<String, ADerivedDefinition> _avpNodes = new HashMap<String, ADerivedDefinition>();
    private Map<String, AEnumDefinition>    _enmNodes = new HashMap<String, AEnumDefinition>();
    private Map<String, AGroupedDefinition> _grpNodes = new HashMap<String, AGroupedDefinition>();
    private Map<String, CommandPair> _commands = new HashMap<String, CommandPair>();

    public SemanticAnalyzer(SemanticAnalyzer parent) {
        _parent = parent;
    }

    public boolean isSatisfied() {
        return _passed;
    }

    /**
     * Returns the grammar of this protocol.
     */
    public AGrammar getGrammar() {
        return _grammar;
    }

    /**
     * Returns grammars of this and all parent protocols.
     */
    public List<AGrammar> getGrammars() {
        List<AGrammar> list = (_parent != null) ? _parent.getGrammars() : new ArrayList<AGrammar>();
        list.add(_grammar);
        return list;
    }

    public Map<String, ADerivedDefinition> getDerivedAVPs() {
        return _avpNodes;
    }

    public Map<String, AEnumDefinition> getEnumeratedAVPs() {
        return _enmNodes;
    }

    public Map<String, AGroupedDefinition> getGroupedAVPs() {
        return _grpNodes;
    }

    public Map<String, CommandPair> getCommands() {
        return _commands;
    }

    public String[][] getAllNamespaces() {
        List<AGrammar> list = getGrammars();
        String[][] names = new String[list.size()][];
        for (int i = 0; i < list.size(); ++i) {
            names[i] = getNamespaces(list.get(i));
        }
        return names;
    }

    public AGrammar getGrammarForAvp(String name) {
        if (_avpNodes.containsKey(name)) {
            return _grammar;
        } else if (_parent != null) {
            return _parent.getGrammarForAvp(name);
        } else {
            return null;
        }
    }

    public SemanticAnalyzer getAnalyzerForAvp(String name) {
        if (_avpNodes.containsKey(name)) {
            return this;
        } else if (_parent != null) {
            return _parent.getAnalyzerForAvp(name);
        } else {
            return null;
        }
    }

    public boolean isAVPDefinitionLocal(String name) {
        return _avpNodes.containsKey(name);
    }

    public static String[] getNamespaces(AGrammar grammar) {
        LinkedList<TIdentifier> namespaces = grammar.getNamespace();
        Iterator<TIdentifier> it = namespaces.iterator();
        String[] names = new String[namespaces.size()];
        for (int i = 0; it.hasNext(); ++i) {
            names[i] = (it.next()).getText();
        }
        return names;
    }

    // Termination: make sure all Enumerated and Grouped AVP types are all defined
    public void outStart(Start node) {
        if (_enumerated.size() > 0) {
            System.err.println("ERROR Undefined enumerated type(s):");
            for (String name: _enumerated.keySet()) {
                System.err.println("\t" + name);
            }
        }
        if (_grouped.size() > 0) {
            System.err.println("ERROR Undefined grouped type(s):");
            for (String name: _grouped.keySet()) {
                System.err.println("\t" + name);
            }
        }

        System.err.println("Total AVP Types: " + _avpNodes.size());
        //System.err.println(_avpNodes);

        System.err.println("Total Enumerated Types: " + _enmNodes.size());
        //System.err.println(_enmNodes);

        System.err.println("Total Grouped Types: " + _grpNodes.size());
        //System.err.println(_grpNodes);

        System.err.println("Total Commands: " + _commands.size());
        //System.err.println(_commands);
    }

    public void inAGrammar(AGrammar node)
    {
        _grammar = node;
    }

    /**
     * Keeps track of all AVP names and codes; Keeps track of all Enumerated and Grouped types.
     */
    public void outADerivedDefinition(ADerivedDefinition node) {
        String name = node.getName().getText();
        String code = node.getAvpCode().getText();
        if (_avpNodes.containsKey(name)) {
            error(node.getName(), "Duplicate AVP name '" + name + '\'');
        } else if (_avpCodes.contains(code)) {
            error(node.getName(), "Duplicate AVP code '" + code + '\'');
        } else if (!new AvpFlagSet((AAvpFlagRules)node.getAvpFlagRules()).isValid()) {
            error(node.getName(), "Invalid AVP flag rules");
        } else {
            _avpNodes.put(name, node);
            _avpCodes.add(code);
        }

        if (node.getAvpType() instanceof AEnumeratedAvpType) {
//System.err.println("-- Enumerated Type detected in " + node.getName());
            _enumerated.put(node.getName().getText(), node);
        } else if (node.getAvpType() instanceof AGroupedAvpType) {
//System.err.println("-- Grouped Type detected in " + node.getName());
            _grouped.put(node.getName().getText(), node);
        }
    }

    // Validates and keeps track of Enumerated definitions
    public void outAEnumDefinition(AEnumDefinition node) {
        String name = node.getName().getText();
        ADerivedDefinition entry = _enumerated.get(name);
        if (entry == null) {
            error(node.getName(), "Unknown AVP in Enumerated specification: " + name);
        } else if (!node.getAvpCode().getText().equals(entry.getAvpCode().getText())) {
            error(node.getName(), "AVP Code does not match original definition: " + name);
//System.err.println("-- Original: [" + entry.getAvpCode().getText() + "], Here: [" + node.getAvpCode().getText() + ']');
        } else {
//System.err.println("-- Enumerated Type " + name + " satisfied");
            _enmNodes.put(name, node);
            _enumerated.remove(name);
        }
    }

    // Validates and keeps track of Grouped definitions
    public void outAGroupedDefinition(AGroupedDefinition node) {
        String name = node.getName().getText();
        ADerivedDefinition entry = _grouped.get(name);
        if (entry == null) {
            error(node.getName(), "Unknown AVP in Grouped specification: " + name);
        } else if (!((AGroupedHeader)node.getGroupedHeader()).getAvpCode().getText().equals(entry.getAvpCode().getText())) {
            error(node.getName(), "AVP Code does not match original definition: " + name);
//System.err.println("-- Original: [" + entry.getAvpCode().getText() + "], Here: [" + node.getAvpCode().getText() + ']');
        } else {
//System.err.println("-- Grouped Type " + name + " satisfied");
            _grpNodes.put(name, node);
            _grouped.remove(name);
        }
    }

    // Validates AVP reference
    public void outANamedAvpRef(ANamedAvpRef node) {
        checkAVPReference(node.getName());
    }

    // Validates AVP reference
    public void outANamedAvpSpec(ANamedAvpSpec node) {
        checkAVPReference(node.getName());
    }

    public void outACommandDefinition(ACommandDefinition node) {
        //_cmdNodes.put(node.getName().getText(), node);
        ACommandHeader header = (ACommandHeader)node.getCommandHeader();
        String name = node.getName().getText();
        if (name.endsWith("-Request")) {
            name = name.substring(0, name.length() - 8);
        } else if (name.endsWith("-Answer")) {
            name = name.substring(0, name.length() - 7);
        }

        CommandPair pair = _commands.get(name);
        if (pair == null) {
            pair = new CommandPair(name, header.getCommandId().getText(), header.getApplicationId(), header.getPxy());
            _commands.put(name, pair);
        }
        if (header.getReq() != null) {
            pair.req = node;
        } else {
            pair.res = node;
        }
    }

    private Set<String> _avpCodes = new HashSet<String>();
    private Map<String, ADerivedDefinition> _enumerated = new HashMap<String, ADerivedDefinition>();
    private Map<String, ADerivedDefinition> _grouped = new HashMap<String, ADerivedDefinition>();

    private void checkAVPReference(Token token) {
//System.err.println("-- Referencing AVP " + token.getText());
        //if (!_avpNodes.containsKey(token.getText())) {
        if (getGrammarForAvp(token.getText()) == null) {
            //error(token, "Unknown AVP in command definition: '" + token.getText() + '\'');
        }
    }

    private void error(Token token, String message) {
        System.err.println("ERROR, line " + token.getLine() + "\n\t" + message);
        _passed = false;
    }

/*
    public void inStart(Start node)
    {
        defaultIn(node);
    }

    public void outStart(Start node)
    {
        defaultOut(node);
    }

    public void outAGrammar(AGrammar node)
    {
        defaultIn(node);
    }

    public void inADerivedDefinition(ADerivedDefinition node)
    {
        defaultIn(node);
    }

    public void inAEnumDefinition(AEnumDefinition node)
    {
        defaultIn(node);
    }

    public void inAGroupedDefinition(AGroupedDefinition node)
    {
        defaultIn(node);
    }

    public void inACommandDefinition(ACommandDefinition node)
    {
        defaultIn(node);
    }

    public void inAOctetStringAvpType(AOctetStringAvpType node)
    {
        defaultIn(node);
    }

    public void outAOctetStringAvpType(AOctetStringAvpType node)
    {
        defaultOut(node);
    }

    public void inAInteger32AvpType(AInteger32AvpType node)
    {
        defaultIn(node);
    }

    public void outAInteger32AvpType(AInteger32AvpType node)
    {
        defaultOut(node);
    }

    public void inAInteger64AvpType(AInteger64AvpType node)
    {
        defaultIn(node);
    }

    public void outAInteger64AvpType(AInteger64AvpType node)
    {
        defaultOut(node);
    }

    public void inAUnsigned32AvpType(AUnsigned32AvpType node)
    {
        defaultIn(node);
    }

    public void outAUnsigned32AvpType(AUnsigned32AvpType node)
    {
        defaultOut(node);
    }

    public void inAUnsigned64AvpType(AUnsigned64AvpType node)
    {
        defaultIn(node);
    }

    public void outAUnsigned64AvpType(AUnsigned64AvpType node)
    {
        defaultOut(node);
    }

    public void inAFloat32AvpType(AFloat32AvpType node)
    {
        defaultIn(node);
    }

    public void outAFloat32AvpType(AFloat32AvpType node)
    {
        defaultOut(node);
    }

    public void inAFloat64AvpType(AFloat64AvpType node)
    {
        defaultIn(node);
    }

    public void outAFloat64AvpType(AFloat64AvpType node)
    {
        defaultOut(node);
    }

    public void inAGroupedAvpType(AGroupedAvpType node)
    {
        defaultIn(node);
    }

    public void outAGroupedAvpType(AGroupedAvpType node)
    {
        defaultOut(node);
    }

    public void inAAddressAvpType(AAddressAvpType node)
    {
        defaultIn(node);
    }

    public void outAAddressAvpType(AAddressAvpType node)
    {
        defaultOut(node);
    }

    public void inATimeAvpType(ATimeAvpType node)
    {
        defaultIn(node);
    }

    public void outATimeAvpType(ATimeAvpType node)
    {
        defaultOut(node);
    }

    public void inAUtf8StringAvpType(AUtf8StringAvpType node)
    {
        defaultIn(node);
    }

    public void outAUtf8StringAvpType(AUtf8StringAvpType node)
    {
        defaultOut(node);
    }

    public void inADiameterIdAvpType(ADiameterIdAvpType node)
    {
        defaultIn(node);
    }

    public void outADiameterIdAvpType(ADiameterIdAvpType node)
    {
        defaultOut(node);
    }

    public void inADiameterUriAvpType(ADiameterUriAvpType node)
    {
        defaultIn(node);
    }

    public void outADiameterUriAvpType(ADiameterUriAvpType node)
    {
        defaultOut(node);
    }

    public void inAEnumeratedAvpType(AEnumeratedAvpType node)
    {
        defaultIn(node);
    }

    public void outAEnumeratedAvpType(AEnumeratedAvpType node)
    {
        defaultOut(node);
    }

    public void inAIpFilterRuleAvpType(AIpFilterRuleAvpType node)
    {
        defaultIn(node);
    }

    public void outAIpFilterRuleAvpType(AIpFilterRuleAvpType node)
    {
        defaultOut(node);
    }

    public void inAQosFilterRuleAvpType(AQosFilterRuleAvpType node)
    {
        defaultIn(node);
    }

    public void outAQosFilterRuleAvpType(AQosFilterRuleAvpType node)
    {
        defaultOut(node);
    }

    public void inAEnumerator(AEnumerator node)
    {
        defaultIn(node);
    }

    public void outAEnumerator(AEnumerator node)
    {
        defaultOut(node);
    }

    public void inAAvpFlagRules(AAvpFlagRules node)
    {
        defaultIn(node);
    }

    public void outAAvpFlagRules(AAvpFlagRules node) {
    }

    public void inAMandatoryAvpFlag(AMandatoryAvpFlag node)
    {
        defaultIn(node);
    }

    public void outAMandatoryAvpFlag(AMandatoryAvpFlag node)
    {
        defaultOut(node);
    }

    public void inAPrivateAvpFlag(APrivateAvpFlag node)
    {
        defaultIn(node);
    }

    public void outAPrivateAvpFlag(APrivateAvpFlag node)
    {
        defaultOut(node);
    }

    public void inAVendorAvpFlag(AVendorAvpFlag node)
    {
        defaultIn(node);
    }

    public void outAVendorAvpFlag(AVendorAvpFlag node)
    {
        defaultOut(node);
    }

    public void inAYesEncryptable(AYesEncryptable node)
    {
        defaultIn(node);
    }

    public void outAYesEncryptable(AYesEncryptable node)
    {
        defaultOut(node);
    }

    public void inANotEncryptable(ANotEncryptable node)
    {
        defaultIn(node);
    }

    public void outANotEncryptable(ANotEncryptable node)
    {
        defaultOut(node);
    }

    public void inAGroupedHeader(AGroupedHeader node)
    {
        defaultIn(node);
    }

    public void outAGroupedHeader(AGroupedHeader node)
    {
        defaultOut(node);
    }

    public void inAGroupedBody(AGroupedBody node)
    {
        defaultIn(node);
    }

    public void outAGroupedBody(AGroupedBody node)
    {
        defaultOut(node);
    }

    public void inACommandHeader(ACommandHeader node)
    {
        defaultIn(node);
    }

    public void outACommandHeader(ACommandHeader node)
    {
        defaultOut(node);
    }

    public void inACommandBody(ACommandBody node)
    {
        defaultIn(node);
    }

    public void outACommandBody(ACommandBody node)
    {
        defaultOut(node);
    }

    public void inANamedAvpRef(ANamedAvpRef node)
    {
        defaultIn(node);
    }

    public void inAGeneralAvpRef(AGeneralAvpRef node)
    {
        defaultIn(node);
    }

    public void outAGeneralAvpRef(AGeneralAvpRef node)
    {
        defaultOut(node);
    }

    public void inAQualifier(AQualifier node)
    {
        defaultIn(node);
    }

    public void outAQualifier(AQualifier node)
    {
        defaultOut(node);
    }

    public void inANamedAvpSpec(ANamedAvpSpec node)
    {
        defaultIn(node);
    }

    public void inAAnyAvpSpec(AAnyAvpSpec node)
    {
        defaultIn(node);
    }

    public void outAAnyAvpSpec(AAnyAvpSpec node)
    {
        defaultOut(node);
    }
*/
}
