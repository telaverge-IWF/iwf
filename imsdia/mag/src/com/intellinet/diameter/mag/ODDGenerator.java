package com.intellinet.diameter.mag;

import java.io.*;
import java.util.*;
import com.intellinet.diameter.mag.analysis.*;
import com.intellinet.diameter.mag.node.*;
import com.intellinet.diameter.mag.util.*;


public class ODDGenerator {
    public ODDGenerator(String filename) throws FileNotFoundException {
        _out = new PrintStream(new FileOutputStream(filename));
        _out.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
        _out.println("<!DOCTYPE dictionary SYSTEM \"dictionary.dtd\">");
        _out.println("<dictionary protocol=\"0\">");
    }

    public void generate(SemanticAnalyzer analyzer) {
        AGrammar node = analyzer.getGrammar();
        _vendor = node.getVendorId();

        boolean isBase = node.getBase() != null;

        if (isBase) {
            _out.print("\t<base uri=");
        } else {
            _out.print("\t<application id=\"");
            _out.print(node.getId().getText());
            _out.print("\" uri=");
        }
        _out.print(node.getUrl().getText()); // quotes included
        _out.println(">");

        writeCommands(analyzer);
        if (isBase) {
            writeTypeDefs();
        }
        writeAVPs(analyzer);
        if (isBase) {
            _out.println("\t</base>");
        } else {
            _out.println("\t</application>");
        }
    }

    public void close() {
        _out.println("</dictionary>");
        _out.close();
    }

    PrintStream _out;
    Map<String, CommandPair> _commands = new HashMap<String, CommandPair>();
    TInteger _vendor;

    private void writeTypeDefs() {
        _out.println("\t\t<typedefn type-name=\"Any\"/>");
        _out.println("\t\t<typedefn type-name=\"OctetString\"/>");
        _out.println("\t\t<typedefn type-name=\"UTF8String\" type-parent=\"OctetString\"/>");
        _out.println("\t\t<typedefn type-name=\"Address\" type-parent=\"OctetString\"/>");
        _out.println("\t\t<typedefn type-name=\"DiameterIdentity\" type-parent=\"OctetString\"/>");
        _out.println("\t\t<typedefn type-name=\"DiameterURI\" type-parent=\"UTF8String\"/>");
        _out.println("\t\t<typedefn type-name=\"IPFilterRule\" type-parent=\"OctetString\"/>");
        _out.println("\t\t<typedefn type-name=\"QOSFilterRule\" type-parent=\"OctetString\"/>");
        _out.println("\t\t<typedefn type-name=\"Integer32\"/>");
        _out.println("\t\t<typedefn type-name=\"Integer64\"/>");
        _out.println("\t\t<typedefn type-name=\"Unsigned32\"/>");
        _out.println("\t\t<typedefn type-name=\"Time\" type-parent=\"Unsigned32\"/>");
        _out.println("\t\t<typedefn type-name=\"Enumerated\" type-parent=\"Unsigned32\"/>");
        _out.println("\t\t<typedefn type-name=\"Unsigned64\"/>");
        _out.println("\t\t<avp name=\"AVP\" code=\"0\">");
        _out.println("\t\t\t<type type-name=\"Any\"/>");
        _out.println("\t\t</avp>");
    }

    private void writeCommands(SemanticAnalyzer analyzer) {
        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet()) {
            writeCommandPair(entry.getValue());
        }
    }

    private void writeAVPs(SemanticAnalyzer analyzer) {
        AGrammar grammar = analyzer.getGrammar();
        Map<String, AEnumDefinition> enumerated = analyzer.getEnumeratedAVPs();
        Map<String, AGroupedDefinition> grouped = analyzer.getGroupedAVPs();
        for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
            writeAVP(entry.getValue(), grammar, enumerated, grouped);
        }
    }

    ///////////////////////////////////////
    // Writers ////////////////////////////
    ///////////////////////////////////////


    private void writeCommandPair(CommandPair pair) {
        _out.print("\t\t<command name=\"");
        if (pair.code == 0) {
            _out.print(pair.name.toUpperCase());
        } else {
            _out.print(pair.name);
        }
        _out.print("\" code=\"");
        _out.print(pair.code);
        _out.print("\"");
        if (pair.appId != null) {
            _out.print(" application-id=\"");
            _out.print(pair.appId.getText());
            _out.print("\"");
        }
        if (pair.proxyable) {
            _out.print(" pbit=\"1\"");
        }
        _out.println(">");

        if (pair.req != null) {
            _out.println("\t\t\t<requestrules>");
            writeCommandAVPList((ACommandBody)pair.req.getCommandBody());
            _out.println("\t\t\t</requestrules>");
        }
        if (pair.res != null) {
            _out.println("\t\t\t<answerrules>");
            writeCommandAVPList((ACommandBody)pair.res.getCommandBody());
            _out.println("\t\t\t</answerrules>");
        }
        _out.println("\t\t</command>");
    }

    private void writeCommandAVPList(ACommandBody body) {
        LinkedList avps;

        if ((avps = body.getFixed()) != null && avps.size() > 0) {
            _out.println("\t\t\t\t<fixed>");
            writeAVPRules(avps);
            _out.println("\t\t\t\t</fixed>");
        }
        if ((avps = body.getRequired()) != null && avps.size() > 0) {
            _out.println("\t\t\t\t<required>");
            writeAVPRules(avps);
            _out.println("\t\t\t\t</required>");
        }
        if ((avps = body.getOptional()) != null && avps.size() > 0) {
            _out.println("\t\t\t\t<optional>");
            writeAVPRules(avps);
            _out.println("\t\t\t\t</optional>");
        }
    }

    private void writeAVPRules(LinkedList list) {
        Iterator it = list.iterator();
        while (it.hasNext()) {
            Node reference = (Node)it.next();
            _out.print("\t\t\t\t\t<avprule");
            if (reference instanceof ANamedAvpRef) {
                ANamedAvpRef named = (ANamedAvpRef)reference;
                _out.print(" name=\"");
                _out.print(named.getName().getText());
                _out.print("\"");
                writeQualifier((AQualifier)named.getQualifier());
            } else {
                AGeneralAvpRef general = (AGeneralAvpRef)reference;
                PAvpSpec spec = general.getAvpSpec();
                _out.print(" name=\"");
                if (spec instanceof ANamedAvpSpec) {
                    _out.print(((ANamedAvpSpec)spec).getName().getText());
                } else { // AAnyAvpSpec
                    _out.print("AVP");
                }
                _out.print("\"");
                writeQualifier((AQualifier)general.getQualifier());
            }
            _out.println("/>");
        }
    }

    private void writeQualifier(AQualifier qualifier) {
        if (qualifier != null) {
            if (qualifier.getMax() != null) {
                _out.print(" maximum=\"");
                _out.print(qualifier.getMax().getText());
                _out.print("\"");
            }
            _out.print(" minimum=\"");
            if (qualifier.getMin() != null) {
                _out.print(qualifier.getMin().getText());
            } else {
                _out.print("0");
            }
            _out.print("\"");
        }
    }

    private void writeAVP(ADerivedDefinition node, AGrammar grammar, Map<String, AEnumDefinition> enumerated, Map<String, AGroupedDefinition> grouped) {
        String name = node.getName().getText();
        _out.print("\t\t<avp name=\"");
        _out.print(name);
        _out.print("\" code=\"");
        _out.print(node.getAvpCode().getText());
        _out.print("\"");
        AAvpFlagRules rules = (AAvpFlagRules)node.getAvpFlagRules();
        writeAVPFlagRules(rules);
        if (node.getAvpType() instanceof AGroupedAvpType) {
            writeAVPVendorId((AGroupedHeader)grouped.get(name).getGroupedHeader());
            _out.println(">");
            AGroupedBody body = (AGroupedBody)grouped.get(name).getGroupedBody();
            _out.println("\t\t\t<grouped>");
            writeGroupedAVPList(body);
            _out.println("\t\t\t</grouped>");
        } else {
            TInteger vendor = node.getVendorId();
            if (vendor == null) {
                vendor = _vendor;
            }
            writeAVPVendorId(rules, vendor);
            _out.println(">");
            _out.print("\t\t\t<type type-name=\"");
            _out.print(OpenDiameterUtil.getDictionaryTypeName(node.getAvpType()));
            _out.println("\"/>");
            if (node.getAvpType() instanceof AEnumeratedAvpType) {
                //_out.print("Enumerated");
                LinkedList enumerators = enumerated.get(name).getEnumerator();
                Iterator it = enumerators.iterator();
                while (it.hasNext()) {
                    AEnumerator enumerator = (AEnumerator)it.next();
                    _out.print("\t\t\t<enum name=\"");
                    _out.print(enumerator.getName().getText());
                    _out.print("\" code=\"");
                    _out.print(enumerator.getValue().getText());
                    _out.println("\"/>");
                }
            }
        }
        _out.println("\t\t</avp>");
    }

    private void writeAVPFlagRules(AAvpFlagRules rules) {
        String[] flags = new AvpFlagSet(rules).getFlags();
        if (flags[AvpFlagSet.MANDATORY] != null) {
            _out.print(" mandatory=\"");
            _out.print(flags[AvpFlagSet.MANDATORY]);
            _out.print("\"");
        }
        if (flags[AvpFlagSet.PROTECTED] != null) {
            _out.print(" protected=\"");
            _out.print(flags[AvpFlagSet.PROTECTED]);
            _out.print("\"");
        }
        /*
         * this flag is implied by the actual vendor id (see writeAVPVendorId)
         *
        if (flags[AvpFlagSet.VENDOR] != null) {
            _out.print(" vendor-id=\"");
            _out.print(flags[AvpFlagSet.VENDOR]);
            _out.print("\"");
        }
        */

        _out.print(" may-encrypt=\"");
        if (rules.getEncryptable() instanceof AYesEncryptable) {
            _out.print("yes");
        } else {
            _out.print("no");
        }
        _out.print("\"");
    }

    private void writeAVPVendorId(AGroupedHeader header) {
        TInteger id = _vendor != null ? _vendor : header.getVendorId();
        if (id != null) {
            _out.print(" vendor-id=\"");
            _out.print(id.getText());
            _out.print("\"");
        }
    }

    private void writeAVPVendorId(AAvpFlagRules rules, TInteger id) {
        String[] flags = new AvpFlagSet(rules).getFlags();
        if (flags[AvpFlagSet.VENDOR] != null && id != null) {
            _out.print(" vendor-id=\"");
            _out.print(id.getText());
            _out.print("\"");
        }
    }

    private void writeGroupedAVPList(AGroupedBody body) {
        LinkedList avps;

        if ((avps = body.getFixed()) != null && avps.size() > 0) {
            _out.println("\t\t\t\t<fixed>");
            writeAVPRules(avps);
            _out.println("\t\t\t\t</fixed>");
        }
        if ((avps = body.getRequired()) != null && avps.size() > 0) {
            _out.println("\t\t\t\t<required>");
            writeAVPRules(avps);
            _out.println("\t\t\t\t</required>");
        }
        if ((avps = body.getOptional()) != null && avps.size() > 0) {
            _out.println("\t\t\t\t<optional>");
            writeAVPRules(avps);
            _out.println("\t\t\t\t</optional>");
        }
    }
}
