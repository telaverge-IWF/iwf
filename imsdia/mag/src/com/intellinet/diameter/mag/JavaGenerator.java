package com.intellinet.diameter.mag;

import java.io.*;
import java.util.*;
import com.intellinet.diameter.mag.analysis.*;
import com.intellinet.diameter.mag.node.*;
import com.intellinet.diameter.mag.util.*;


public class JavaGenerator {
    private static final String FIXED_BUT_MISSING = "[fixed but missing]";
    private static final String REQED_BUT_MISSING = "[required but missing]";
    private static final String THERE_BUT_MISSING = "[said present but missing]";

    public JavaGenerator(String pathname) {
        validate(_srcRoot = new File(pathname, "src"));
        validate(_tstRoot = new File(pathname, "test"));
    }

    /**
     * Processes one protocol/application. This method is to be called many times, once for each diameter application.
     */
    public void process(SemanticAnalyzer analyzer) throws IOException {
        String fs = System.getProperty("file.separator");
        _protocolId = analyzer.getGrammar().getId().getText();
        _namespaces = analyzer.getAllNamespaces();
        String[] myNamespace = _namespaces[_namespaces.length - 1];
        StringBuffer path = new StringBuffer(myNamespace[0]);
        for (int i = 1; i < myNamespace.length; ++i) {
            path.append(fs).append(myNamespace[i]);
        }
        _protocolName = capitalize(myNamespace[myNamespace.length-1]);
        validate(_srcDirectory = new File(_srcRoot, path.toString()));
        validate(_tstDirectory = new File(_tstRoot, path.toString()));

        processProtocol(analyzer);
        processAvps(analyzer);
        processCommands(analyzer);
    }


    private final File _srcRoot, _tstRoot;

    private File _srcDirectory, _tstDirectory;
    private String[][] _namespaces;
    private String _protocolName;
    private String _protocolId;

    private static final void validate(File dir) {
        try {
            if (!dir.exists()) {
//System.err.println("Attempting to create " + dir.getCanonicalPath());
                if (!dir.mkdirs()) {
                    throw new IllegalArgumentException("Directory '" + dir.getCanonicalPath() + "' does not exist and cannot be created");
                }
            } else if (!dir.isDirectory()) {
                throw new IllegalArgumentException("Path '" + dir.getCanonicalPath() + "' exists and is not a directory");
            }
        } catch (IOException x) {
            throw new IllegalArgumentException(x);
        }
    }

    private static final String capitalize(String text) {
        char[] chars = text.toCharArray();
        chars[0] = Character.toTitleCase(chars[0]);
        return new String(chars);
    }

    public static final String decapitalize(String text) {
        char[] chars = text.toCharArray();
        chars[0] = Character.toLowerCase(chars[0]);
        return new String(chars);
    }

    private static final void openNamespaces(PrintWriter pw, String[] name) {
        pw.print("package ");
        pw.print(name[0]);
        for (int i = 1; i < name.length; ++i) {
            pw.print('.'); pw.print(name[i]);
        }
        pw.println(';');
        pw.println();
    }

    private static final void closeNamespaces(PrintWriter pw, String[] name) {
    }

    private static final void printNamespaces(PrintWriter pw, String[] name) {
        for (int i = 0; i < name.length; ++i) {
            pw.print(name[i] + '.');
        }
    }

/*
    private static final void printAvpIncludes(PrintWriter pw, String[][] names) {
        for (int i = 0; i < names.length; ++i) {
            pw.print("import ");
            for (int j = 0; j < names[i].length; ++j) {
                pw.print(names[i][j]); pw.print('.');
            }
            pw.print(capitalize(names[i][names[i].length - 1])); pw.println("*;");
        }
    }
*/

    private static final void printDerivedClassName(PrintWriter pw, PAvpType avpType) {
        pw.print("DerivedAVP<");
            pw.print(OpenDiameterUtil.getJavaValueTypeName(avpType));
        pw.print('>');
    }

    private static final void printAttributeName(PrintWriter pw, SemanticAnalyzer analyzer, String name) {
        AGrammar grammar = analyzer.getGrammarForAvp(name);
        String[] namespaces = SemanticAnalyzer.getNamespaces(grammar);
        if (grammar != analyzer.getGrammar()) {
            for (int i = 0; i < namespaces.length; ++i) {
                pw.print(namespaces[i]);
                pw.print('.');
            }
        }
        pw.print(capitalize(namespaces[namespaces.length - 1])); pw.print("AttributeName."); pw.print(name.replaceAll("-", ""));
    }

    public static final String getTypeReference(SemanticAnalyzer analyzer, String name) {
        StringBuffer sb = new StringBuffer();
        AGrammar grammar = analyzer.getGrammarForAvp(name);
        String[] namespaces = SemanticAnalyzer.getNamespaces(grammar);
        if (grammar != analyzer.getGrammar()) {
            for (int i = 0; i < namespaces.length; ++i) {
                sb.append(namespaces[i]);
                sb.append(".");
            }
        }
        sb.append(name.replaceAll("-", ""));
        return sb.toString();
    }

    public static final void printTypeReference(PrintWriter pw, SemanticAnalyzer analyzer, String name) {
        pw.print(getTypeReference(analyzer, name));
    }

    private void processProtocol(SemanticAnalyzer analyzer) throws IOException {
        File file = new File(_srcDirectory, "package-info.java");
//System.err.println("Generating package info file " + file.getCanonicalPath());
        PrintWriter source = new PrintWriter(new FileWriter(file));
        DocumentWriter.generateForProtocol(source, analyzer.getGrammar());
        openNamespaces(source, _namespaces[_namespaces.length - 1]);
        source.close();
    }

    private void processAvps(SemanticAnalyzer analyzer) throws IOException {
        File file = new File(_srcDirectory, _protocolName + "AttributeName.java");
//System.err.println("Generating source file " + file.getCanonicalPath());
        PrintWriter source = new PrintWriter(new FileWriter(file));
        openNamespaces(source, _namespaces[_namespaces.length - 1]);
        //printAvpIncludes(source, _namespaces);
        source.println("import com.intellinet.diameter.*;");
        source.println();

        // Generate attribute names declarations
        DocumentWriter.generateForAttributeNames(source, _namespaces[_namespaces.length - 1][_namespaces[_namespaces.length - 1].length-1]);
        source.print("public abstract class "); source.print(_protocolName); source.println("AttributeName {");
        // Generate attribute names definitions
        for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
            String avpName = entry.getValue().getName().getText();
            String clsName = avpName.replaceAll("-", "");
            String avpType = OpenDiameterUtil.getCxxTypeName(entry.getValue().getAvpType());

            source.println();
            source.print("    private static class "); source.print(clsName);
            source.println("AVPBuilder implements com.intellinet.diameter.AVPBuilder {");
            source.println("        public AVP build(com.intellinet.diameter.Data impl) {");
            source.print  ("            return new ");
                source.print(clsName); source.print("((com.intellinet.diameter."); source.print(avpType);
            source.println("Data)impl);");
            source.println("        }");
            source.println("    }");
            source.println();
            source.print("    public static final AttributeName "); source.print(clsName);
                source.print(" = new com.intellinet.diameter.");
                source.print(avpType); source.print("Name(\"");
                source.print(avpName); source.print("\", new ");
                source.print(clsName);
            source.println("AVPBuilder());");
        }
        source.println("}");
        source.println();
        closeNamespaces(source, _namespaces[_namespaces.length - 1]);
        source.close();

        // Generate AVP classes
        for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
            String avpName = entry.getValue().getName().getText();
            String clsName = avpName.replaceAll("-", "");
            generateAvpClass(avpName, clsName, entry.getValue(), analyzer);
        }
    }

    private void processCommands(SemanticAnalyzer analyzer) throws IOException {
        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet()) {
            CommandPair pair = entry.getValue();

            if (pair.req != null) {
                File file = new File(_srcDirectory, pair.req.getName().getText().replaceAll("-", "") + ".java");
//System.err.println("Generating header file " + file.getCanonicalPath());
                PrintWriter source = new PrintWriter(new FileWriter(file));
                openNamespaces(source, _namespaces[_namespaces.length - 1]);
                //printAvpIncludes(source, _namespaces);
                source.println("import com.intellinet.diameter.*;");

                generateCommandClass(source, analyzer, true, pair.code, pair.req);
                closeNamespaces(source, _namespaces[_namespaces.length - 1]);
                source.close();
            }

            if (pair.res != null) {
                File file = new File(_srcDirectory, pair.res.getName().getText().replaceAll("-", "") + ".java");
//System.err.println("Generating header file " + file.getCanonicalPath());
                PrintWriter source = new PrintWriter(new FileWriter(file));
                openNamespaces(source, _namespaces[_namespaces.length - 1]);
                //printAvpIncludes(source, _namespaces);
                source.println("import com.intellinet.diameter.*;");

                generateCommandClass(source, analyzer, false, pair.code, pair.res);
                closeNamespaces(source, _namespaces[_namespaces.length - 1]);
                source.close();
            }

            String clsName = pair.name.replaceAll("-", "");
            File file = new File(_tstDirectory, clsName + "Test.java");
            PrintWriter tester = new PrintWriter(new FileWriter(file));
            openNamespaces(tester, _namespaces[_namespaces.length - 1]);
            tester.println("import com.intellinet.diameter.*;");
            tester.println("import diameter.*;");
            tester.println();

            tester.print("public class "); tester.print(clsName); tester.println("Test {");
            if (pair.req != null) JavaTestingUtil.generateCommandTester(tester, analyzer, pair.req);
            if (pair.res != null) JavaTestingUtil.generateCommandTester(tester, analyzer, pair.res);
            tester.println();
            tester.println("    public static void main(String[] args) throws Exception {");
            if (pair.req != null) {
                tester.print("        test"); tester.print(pair.req.getName().getText().replaceAll("-", "")); tester.println("();");
            }
            if (pair.res != null) {
                tester.print("        test"); tester.print(pair.res.getName().getText().replaceAll("-", "")); tester.println("();");
            }
            tester.println("    }");
            tester.println('}');
            tester.close();
        }
    }

    private void generateAvpClass(String avpName, String clsName, ADerivedDefinition node, SemanticAnalyzer analyzer) throws IOException {
        File file = new File(_srcDirectory, clsName + ".java");
//System.err.println("Generating source file " + file.getCanonicalPath());
        PrintWriter source = new PrintWriter(new FileWriter(file));
        openNamespaces(source, _namespaces[_namespaces.length - 1]);
        //printAvpIncludes(source, _namespaces);
        source.println("import com.intellinet.diameter.*;");
        source.println();

//System.err.println("Generating class " + clsName);
        source.println();
        DocumentWriter.generateForClass(source, node);
        if (node.getAvpType() instanceof AGroupedAvpType) {
            source.print("public class "); source.print(clsName); source.println(" extends com.intellinet.diameter.GroupedAVP {");
            // the constructors
            DocumentWriter.generateForGroupedAVPConstructor(source, clsName);
            source.print("    public "); source.print(clsName); source.println("() {}");
            source.println();
            source.print("    "); source.print(clsName); source.println("(com.intellinet.diameter.GroupedData data) {");
            source.println("        super(data);");
            source.println("    }");
            // the accessors
            generateGroupedAVPAccessors(source, analyzer, avpName, clsName);
            // the print function
            source.println();
            generateGroupedPrinter(source, clsName, analyzer.getGroupedAVPs().get(avpName));
        } else {
            String valueType;
            String dataType;
            source.print("public class "); source.print(clsName); source.print(" extends com.intellinet.diameter."); printDerivedClassName(source, node.getAvpType());
            source.println(" {");
            if (node.getAvpType() instanceof AEnumeratedAvpType) {
                source.print("    public static enum Value ");
                Iterator<PEnumerator> it = analyzer.getEnumeratedAVPs().get(avpName).getEnumerator().iterator();
                char eol = '{';
                while (it.hasNext()) {
                    source.println(eol);
                    AEnumerator enumerator = (AEnumerator)it.next();
                    source.print("        ");
                    source.print(enumerator.getName().getText());
                    source.print("(");
                    source.print(enumerator.getValue().getText());
                    source.print(")");
                    eol = ',';
                }
                source.println(';');
                source.println();
                source.println("        public final int id;");
                source.println();
                source.println("        private Value(int id) { this.id = id; }");
                source.println("    };");
                source.println();
                valueType = "Value";
                dataType = OpenDiameterUtil.getCxxTypeName(node.getAvpType());
            } else {
                valueType = OpenDiameterUtil.getJavaValueTypeName(node.getAvpType());
                dataType = OpenDiameterUtil.getCxxTypeName(node.getAvpType());
            }
            DocumentWriter.generateForDerivedAVPConstructor(source, clsName, "value");
            source.print("    public "); source.print(clsName); source.print('('); source.print(valueType); source.println(" value) {");
            source.print("        super(new com.intellinet.diameter."); source.print(dataType); source.print("Data(");
            if (valueType.equals("Value")) {
                source.print("value.id));");
            } else {
                source.println("value));");
            }
            source.println("    }");
            source.println();
            source.print("    "); source.print(clsName); source.print("(com.intellinet.diameter."); source.print(dataType); source.println("Data data) {");
            source.println("        super(data);");
            source.println("    }");
        }

        source.println("}");
        closeNamespaces(source, _namespaces[_namespaces.length - 1]);
        source.close();
    }

    private void generateGroupedAVPAccessors(PrintWriter s, SemanticAnalyzer analyzer, String avpName, String clsName) {
        AGroupedDefinition node = analyzer.getGroupedAVPs().get(avpName);
        AGroupedBody body = (AGroupedBody)node.getGroupedBody();
        generateAVPAccessors(s, analyzer, clsName, 1, body.getFixed().iterator());
        generateAVPAccessors(s, analyzer, clsName, 1, body.getRequired().iterator());
        generateAVPAccessors(s, analyzer, clsName, 0, body.getOptional().iterator());
    }

    private void generateGroupedPrinter(PrintWriter source, String clsName, AGroupedDefinition node) {
        source.println();
        source.println("    public String toString() {");
        source.println("        StringBuffer sb = new StringBuffer(\" {\\n\");");
        AGroupedBody body = (AGroupedBody)node.getGroupedBody();
        generateAVPPrinting(source, clsName, 1, body.getFixed().iterator(), FIXED_BUT_MISSING);
        generateAVPPrinting(source, clsName, 1, body.getRequired().iterator(), REQED_BUT_MISSING);
        generateAVPPrinting(source, clsName, 0, body.getOptional().iterator(), THERE_BUT_MISSING);
        source.println("        return sb.append('}').toString();");
        source.println("    }");
    }

    private void generateCommandClass(PrintWriter s, SemanticAnalyzer analyzer, boolean request, int code, ACommandDefinition node) {
        String clsName = node.getName().getText().replaceAll("-", "");
        ACommandHeader head = (ACommandHeader)node.getCommandHeader();
        String proxyable = head.getPxy() != null ? "true" : "false";
        s.println();
        s.println();
        DocumentWriter.generateForClass(s, node);
        s.print("public class "); s.print(clsName); s.println(" extends com.intellinet.diameter.Command {");

        // the constructors
        DocumentWriter.generateForCommandConstructor(s, clsName);
        s.print  ("    public "); s.print(clsName); s.println("(boolean error, boolean retrans) {");
        s.print  ("        super(");
            s.print(request); s.print(", "); s.print(proxyable); s.print(", error, retrans, ");
            s.print(head.getCommandId().getText()); s.print(", "); s.print(_protocolId);
        s.println(");");
        s.println("    }");
        s.println();

        DocumentWriter.generateForCommandConstructor(s, clsName, "buffer", null);
        s.print  ("    public "); s.print(clsName); s.println("(byte[] buffer) throws WrongCommandTypeException, CodecException {");
        s.println("        super(buffer);");
        if (code > 0) s.println("        validate();");
        s.println("    }");
        s.println();

        DocumentWriter.generateForCommandConstructor(s, clsName, "generic");
        s.print  ("    public "); s.print(clsName); s.println("(GenericCommand generic) throws WrongCommandTypeException {");
        s.println("        super(generic.transfer());");
        if (code > 0) s.println("        validate();");
        s.println("    }");
        s.println();

        s.print  ("    "); s.print(clsName); s.println("(com.intellinet.diameter.CommandData data) throws WrongCommandTypeException {");
        s.println("        super(data);");
        if (code > 0) s.println("        validate();");
        s.println("    }");

        // the accessors
        generateCommandAVPAccessors(s, analyzer, clsName, node);
        s.println();
        generateCommandPrinter(s, clsName, node);
        if (code > 0) {
            s.println();
            s.println("    private void validate() throws WrongCommandTypeException {");
            s.print  ("        if (getCommandCode() != "); s.print(head.getCommandId().getText());
                s.print(request ? " || !" : " || "); s.println("isRequest()) {");
            s.println("            throw new WrongCommandTypeException(getCommandName());");
            s.println("        }");
            s.println("    }");
        }
        s.println("}");
    }

    private void generateCommandAVPAccessors(PrintWriter s, SemanticAnalyzer analyzer, String clsName, ACommandDefinition node) {
        ACommandBody body = (ACommandBody)node.getCommandBody();
        generateAVPAccessors(s, analyzer, clsName, 1, body.getFixed().iterator());
        generateAVPAccessors(s, analyzer, clsName, 1, body.getRequired().iterator());
        generateAVPAccessors(s, analyzer, clsName, 0, body.getOptional().iterator());
    }

    private void generateCommandPrinter(PrintWriter source, String clsName, ACommandDefinition node) {
        source.println("    public String toString() {");
        source.println("        StringBuffer sb = headerToStringBuffer().append(\" {\\n\");");
        ACommandBody body = (ACommandBody)node.getCommandBody();
        generateAVPPrinting(source, clsName, 1, body.getFixed().iterator(), FIXED_BUT_MISSING);
        generateAVPPrinting(source, clsName, 1, body.getRequired().iterator(), REQED_BUT_MISSING);
        generateAVPPrinting(source, clsName, 0, body.getOptional().iterator(), THERE_BUT_MISSING);
        source.println("        return sb.append('}').toString();");
        source.println("    }");
    }


    // Shared by AVPs and Commands

    private void generateAVPAccessors(PrintWriter source, SemanticAnalyzer analyzer, String clsName, int minOccurance, Iterator it) {
        while (it.hasNext()) {
            Object node = it.next();
            if (node instanceof ANamedAvpRef) {
                generateAccessors(source, analyzer, clsName, ((ANamedAvpRef)node).getQualifier(), minOccurance, ((ANamedAvpRef)node).getName().getText());
            } else { //AGeneralAvpRef
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                if (spec instanceof ANamedAvpSpec) {
                    generateAccessors(source, analyzer, clsName, ((AGeneralAvpRef)node).getQualifier(), minOccurance, ((ANamedAvpSpec)spec).getName().getText());
                } else { // AAnyAvpSpec
                    generateAccessors(source, analyzer, clsName, ((AGeneralAvpRef)node).getQualifier(), minOccurance);
                }
            }
        }
    }

    private void generateAVPPrinting(PrintWriter source, String clsName, int minOccurance, Iterator it, String message) {
        boolean hasExtra = false;
        Qualifier qualifier;
        String name;

        while (it.hasNext()) {
            Object node = it.next();
            if (node instanceof ANamedAvpRef) {
                qualifier = new Qualifier((AQualifier)((ANamedAvpRef)node).getQualifier(), minOccurance);
                name = ((ANamedAvpRef)node).getName().getText().replaceAll("-", "");
            } else { //AGeneralAvpRef
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                if (spec instanceof ANamedAvpSpec) {
                    qualifier = new Qualifier((AQualifier)((AGeneralAvpRef)node).getQualifier(), minOccurance);
                    name = ((ANamedAvpSpec)spec).getName().getText().replaceAll("-", "");
                } else { // AAnyAvpSpec
                    hasExtra = true;
                    continue;
                }
            }
            if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
                source.print("        for (int i = 0; i < count"); source.print(name); source.println("(); ++i) {");
                source.print("            sb.append(\"    "); source.print(name); source.println(":\");");
                generateAVPAppender(source, name, "(i)", THERE_BUT_MISSING);
                source.println("        }");
            } else if (qualifier.getMin() < 1) {
                source.print("        if (contains"); source.print(name); source.println("()) {");
                source.print("            sb.append(\"    "); source.print(name); source.println(":\");");
                generateAVPAppender(source, name, "()", THERE_BUT_MISSING);
                source.println("        }");
            } else {
                source.print("        sb.append(\"    "); source.print(name); source.println(":\");");
                generateAVPAppender(source, name, "()", message);
            }
        }
        if (hasExtra) {
            source.println("        sb.append(\"    ANY:\").append(_data.getContainer().extrasToString()).append('\\n');");
        }
    }

    private static void generateAVPAppender(PrintWriter source, String name, String args, String message) {
        source.println("            try {");
        source.print  ("                sb.append(get"); source.print(name); source.print(args); source.println(").append('\\n');");
        source.println("            } catch (NoSuchAttributeException x) {");
        source.print  ("                sb.append(\""); source.print(message); source.println("\\n\");");
        source.println("            }");
    }

    // Generate accessors for a named AVP
    private void generateAccessors(PrintWriter s, SemanticAnalyzer analyzer, String clsName, PQualifier qual, int min, String avpName) {
        String name = avpName.replaceAll("-", "");
//System.err.println("generateAccessors for " + name + ", qual = " + qual + ", min = " + min);
        String setter = "set";
        boolean single = true;
        String getopt = "";
        String getarg = "0";

        Qualifier qualifier = new Qualifier((AQualifier)qual, min);

        // Tester
        if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
            s.println();
            DocumentWriter.generateForCounter(s, name);
            s.print("    public int count"); s.print(name); s.println("() {");
            s.print("        return _data.getContainer().count("); printAttributeName(s, analyzer, avpName); s.println(");");
            s.println("    }");
            setter = "add";
            single = false;
            getopt = "int index";
            getarg = "index";
        } else if (qualifier.getMin() < 1) {
            s.println();
            DocumentWriter.generateForTester(s, name);
            s.print("    public boolean contains"); s.print(name); s.println("() {");
            s.print("        return _data.getContainer().contains("); printAttributeName(s, analyzer, avpName); s.println(");");
            s.println("    }");
        }

        // Getter
        s.println();
        DocumentWriter.generateForGetter(s, name, single ? null : "index");
        s.print  ("    public ");
            printTypeReference(s, analyzer, avpName); s.print(" get"); s.print(name); s.print("("); s.print(getopt);
        s.println(") throws NoSuchAttributeException {");

        s.print  ("        return ("); printTypeReference(s, analyzer, avpName);
            s.print(")_data.getContainer().get("); printAttributeName(s, analyzer, avpName); s.print(", "); s.print(getarg);
        s.println(");");
        s.println("    }");

        // Setter
        s.println();
        DocumentWriter.generateForSetter(s, name, "avp", single);
        s.print("    public void ");
            s.print(setter); s.print(name); s.print("("); printTypeReference(s, analyzer, avpName);
        s.println(" avp) {");
        s.print("        _data.getContainer().add(");
            printAttributeName(s, analyzer, avpName); s.print(", avp.getData(), "); s.print(single);
        s.println(");");
        s.println("    }");
    }

    // generate accessors for "any" AVPs
    private void generateAccessors(PrintWriter s, SemanticAnalyzer analyzer, String clsName, PQualifier qual, int min) {
//System.err.println("generateAccessors for ANY, qual = " + qual + ", min = " + min);
        String setter = "set";
        boolean single = true;
        String getopt = "";
        String getarg = "0";

        Qualifier qualifier = new Qualifier((AQualifier)qual, min);

        // Tester
        if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
            s.println();
            DocumentWriter.generateForAnyCounter(s, null);
            s.println("    public int countExtra() {");
            s.println("        return _data.getContainer().count(AttributeName.AVP);");
            s.println("    }");
            s.println();
            DocumentWriter.generateForAnyCounter(s, "name");
            s.println("    public int countExtra(AttributeName name) {");
            s.println("        return _data.getContainer().countExtra(name);");
            s.println("    }");
            setter = "add";
            single = false;
            getopt = ", int index";
            getarg = "index";
        } else if (qualifier.getMin() < 1) {
            s.println();
            DocumentWriter.generateForAnyTester(s, null);
            s.println("    public boolean containsExtra() {");
            s.println("        return _data.getContainer().contains(AttributeName.AVP);");
            s.println("    }");
            s.println();
            DocumentWriter.generateForAnyTester(s, "name");
            s.println("    public boolean containsExtra(AttributeName name) {");
            s.println("        return _data.getContainer().containsExtra(name);");
            s.println("    }");
        }

        // Getter
        s.println();
        DocumentWriter.generateForAnyGetter(s, "name", single ? null : getarg);
        s.print  ("    public AVP getExtra(AttributeName name"); s.print(getopt); s.println(") throws NoSuchAttributeException {");
        s.print  ("        return _data.getContainer().getExtra(name, "); s.print(getarg); s.println(");");
        s.println("    }");

        // Setter
        s.println();
        DocumentWriter.generateForAnySetter(s, "avp", single);
        s.print  ("    public void "); s.print(setter); s.println("Extra(AVP avp) {");
        s.print  ("        _data.getContainer().add(AttributeName.AVP, avp.getData(), "); s.print(single); s.println(");");
        s.println("    }");
    }
}
