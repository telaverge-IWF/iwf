package com.intellinet.diameter.mag;

import java.io.*;
import java.util.*;
import com.intellinet.diameter.mag.node.*;
import com.intellinet.diameter.mag.util.*;


public class JavaTestingUtil {
    private static Random _random = new Random();

    public static void generateCommandTester(PrintWriter pw, SemanticAnalyzer analyzer, ACommandDefinition node) {
        String name = node.getName().getText();
        String identifier = name.replaceAll("-", "");
        String var = JavaGenerator.decapitalize(identifier);
        pw.println();
        pw.print("    public static void test"); pw.print(identifier); pw.println("() throws Exception {");
        pw.print("        "); pw.print(identifier);

        boolean error = ((ACommandHeader)node.getCommandHeader()).getErr() != null;
        pw.print(' '); pw.print(var); pw.print(" = new "); pw.print(identifier); pw.print("("); pw.print(error); pw.print(", false);");
        pw.println();
        ACommandBody body = (ACommandBody)node.getCommandBody();

        writeObjectComposer(pw, analyzer, name, 2, body.getFixed().iterator(), body.getRequired().iterator(), body.getOptional().iterator());

        pw.println();
        pw.print("        "); pw.print("byte[] buffer = "); pw.print(var); pw.println(".encode();");
        pw.print("        "); pw.print(identifier);
        pw.print(' '); pw.print(var); pw.print("2 = new "); pw.print(identifier); pw.println("(buffer);");
        pw.print("        String s1 = "); pw.print(var); pw.println(".toString();");
        pw.print("        String s2 = "); pw.print(var); pw.println("2.toString();");
        pw.print("        "); pw.println("if (!s1.equals(s2)) {");
        pw.print("            System.err.println(\""); pw.print(var); pw.println("1 = \" + s1);");
        pw.print("            System.err.println(\""); pw.print(var); pw.println("2 = \" + s2);");
        pw.print("            throw new VerificationException(\""); pw.print(identifier); pw.println(" encoding/decoding failure\");");
        pw.println("        }");
        pw.println("    }");
    }

    private static void writeObjectComposer(PrintWriter pw, SemanticAnalyzer analyzer, String name, int level, Iterator fixed, Iterator req, Iterator opt) {
        String var = JavaGenerator.decapitalize(name.replaceAll("-", ""));
        writeSetter(pw, analyzer, var, level, 1, fixed);
        writeSetter(pw, analyzer, var, level, 1, req);
        writeSetter(pw, analyzer, var, level, 0, opt);
    }

    private static void writeSetter(PrintWriter pw, SemanticAnalyzer analyzer, String var, int level, int minOccurance, Iterator it) {
        boolean hasExtra = false;
        while (it.hasNext()) {
            Object node = it.next();
            Qualifier qualifier;
//System.err.println(node.getClass().getName());
            String name;
            if (node instanceof ANamedAvpRef) {
                qualifier = new Qualifier((AQualifier)((ANamedAvpRef)node).getQualifier(), minOccurance);
                name = ((ANamedAvpRef)node).getName().getText();
            } else { //AGeneralAvpRef
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                if (spec instanceof ANamedAvpSpec) {
                    qualifier = new Qualifier((AQualifier)((AGeneralAvpRef)node).getQualifier(), minOccurance);
                    name = ((ANamedAvpSpec)spec).getName().getText();
                } else { // AAnyAvpSpec
                    hasExtra = true;
                    continue;
                }
            }
if (name.equals("Failed-AVP")) {
    continue;
}
            SemanticAnalyzer analyzerForAvp = analyzer.getAnalyzerForAvp(name);
//System.err.println("DerivedDefinition: " + name);
            String identifier = name.replaceAll("-", "");
            ADerivedDefinition definition = analyzerForAvp.getDerivedAVPs().get(name);
            PAvpType type = definition.getAvpType();

            if (type instanceof AGroupedAvpType) {
                AGroupedDefinition grouped = analyzerForAvp.getGroupedAVPs().get(name);
                AGroupedBody body = (AGroupedBody)grouped.getGroupedBody();
                for (int i = 0; i < level; ++i) pw.print("    "); pw.println('{');
                for (int i = 0; i < level+1; ++i) pw.print("    "); JavaGenerator.printTypeReference(pw, analyzer, name);
                pw.print(' '); pw.print(JavaGenerator.decapitalize(identifier));
                pw.print(" = new "); JavaGenerator.printTypeReference(pw, analyzer, name); pw.println("();");
                writeObjectComposer(pw, analyzer, name, level+1, body.getFixed().iterator(), body.getRequired().iterator(), body.getOptional().iterator());
            }

            for (int i = 0; i < level; ++i) pw.print("    ");
            if (type instanceof AGroupedAvpType) {
                pw.print("    ");
            }
            pw.print(var);
            if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
                pw.print(".add");
            } else {
                pw.print(".set");
            }

            pw.print(identifier);
            if (type instanceof AGroupedAvpType) {
                pw.print("("); pw.print(JavaGenerator.decapitalize(identifier)); pw.println(");");
                for (int i = 0; i < level; ++i) pw.print("    "); pw.println('}');
            } else {
                pw.print("(new "); JavaGenerator.printTypeReference(pw, analyzer, name);
                    pw.print("("); pw.print(JavaTestingUtil.getJavaValue(analyzer, definition));
                pw.println("));");
            }
        }
        if (hasExtra) {
            for (int i = 0; i < level; ++i) pw.print("    "); pw.print("// add more AVP as ANY values to "); pw.println(var);
        }
    }

    public static String getJavaValue(SemanticAnalyzer analyzer, ADerivedDefinition node) {
        PAvpType type = node.getAvpType();

        StringBuffer sb = new StringBuffer();
        if (type instanceof AOctetStringAvpType) {
            sb.append("\"octetstring").append(_random.nextInt()).append('"');
        } else if (type instanceof AInteger32AvpType) {
            sb.append("new Integer(").append(_random.nextInt()).append(')');
        } else if (type instanceof AInteger64AvpType) {
            sb.append("new Long(").append(_random.nextLong()).append('L').append(')');
        } else if (type instanceof AUnsigned32AvpType) {
            sb.append("new Integer(").append(_random.nextInt()).append(')');
        } else if (type instanceof AUnsigned64AvpType) {
            sb.append("new Long(").append(_random.nextLong()).append('L').append(')');
        } else if (type instanceof AFloat32AvpType) {
	    sb.append("new Float(").append(_random.nextFloat()).append('"').append(')');
        } else if (type instanceof AFloat64AvpType) {
	    sb.append("new Double(").append(_random.nextFloat()).append('"').append(')');
        } else if (type instanceof AAddressAvpType) {
            sb.append("new Address(Address.Family.IPV4, \"")
              .append(_random.nextInt() & 0x00FF).append('.')
              .append(_random.nextInt() & 0x00FF).append('.')
              .append(_random.nextInt() & 0x00FF).append('.')
              .append(_random.nextInt() & 0x00FF).append("\")");
        } else if (type instanceof ATimeAvpType) {
            sb.append(_random.nextInt());
        } else if (type instanceof AUtf8StringAvpType) {
            sb.append("\"utf8string").append(_random.nextInt()).append('"');
        } else if (type instanceof ADiameterIdAvpType) {
            sb.append("\"id").append(_random.nextInt()).append(".diameter.com\"");
        } else if (type instanceof ADiameterUriAvpType) {
            sb.append("new URI(\"domain").append(_random.nextInt()).append(".com\", URI.Scheme.AAAS, (short)").append(_random.nextInt() & 0x7FFF)
              .append(", URI.Transport.TCP, URI.Protocol.DIAMETER)");
        } else if (type instanceof AIpFilterRuleAvpType) {
            sb.append("new IPFilterRule()");
        //} else if (type instanceof AQosFilterRuleAvpType) {
        //    return "QoSFilterRule";
        } else if (type instanceof AEnumeratedAvpType) {
            String name = node.getName().getText();
            SemanticAnalyzer analyzerForAvp = analyzer.getAnalyzerForAvp(name);
            List enumerators = analyzerForAvp.getEnumeratedAVPs().get(name).getEnumerator();
            AEnumerator item = (AEnumerator)enumerators.get(_random.nextInt(enumerators.size()));
/*
System.err.println("JavaTestingUtil: " + node.getName().getText() + " has " + enumerators.size() + " enumerators");
Iterator it = enumerators.iterator();
while (it.hasNext()) {
System.err.print("    "); System.err.println(((AEnumerator)it.next()).getName().getText());
}
System.err.println("JavaTestingUtil: => " + item.getName().getText());
*/
            sb.append(JavaGenerator.getTypeReference(analyzer, name)).append(".Value.").append(item.getName().getText());
        } else {
            throw new RuntimeException("Unknow AVP type [" + type.getClass().getName() + "]");
        }

        return sb.toString();
    }
}
