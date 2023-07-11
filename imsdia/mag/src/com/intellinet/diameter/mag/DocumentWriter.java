package com.intellinet.diameter.mag;

import java.io.*;
import java.util.*;
import com.intellinet.diameter.mag.analysis.*;
import com.intellinet.diameter.mag.node.*;
import com.intellinet.diameter.mag.util.*;


public class DocumentWriter {

    // Protocol/package Documents

    public static void generateForProtocol(PrintWriter source, AGrammar grammar) {
        TDocumentation doc = grammar.getDocumentation();
        if (doc != null) {
            source.println(doc.getText().replaceAll("\n    ", "\n"));
        }
    }

    // Attribute Names Documents

    public static void generateForAttributeNames(PrintWriter source, String namespace) {
        source.println("/**");
        source.print  (" * This class defines singleton AttributeName instances for all attributes in <i><b>");
            source.print(namespace);
        source.println("</b></i>.");
        source.println(" */");
    }

    // Class Documents

    public static void generateForClass(PrintWriter source, ADerivedDefinition node) {
        TDocumentation doc = node.getDocumentation();
        if (doc != null) {
            source.println(doc.getText().replaceAll("\n    ", "\n"));
        }
    }

    public static void generateForClass(PrintWriter source, ACommandDefinition node) {
        TDocumentation doc = node.getDocumentation();
        if (doc != null) {
            source.println(doc.getText().replaceAll("\n    ", "\n"));
        }
    }

    // AVP Constructor Documents

    public static void generateForGroupedAVPConstructor(PrintWriter source, String className) {
        source.println("    /**");
        source.print  ("     * Constructs a new "); source.print(className); source.println('.');
        source.println("     */");
    }

    public static void generateForDerivedAVPConstructor(PrintWriter source, String className, String valueName) {
        source.println("    /**");
        source.print  ("     * Constructs a "); source.print(className); source.println(" with the given value.");
        source.println("     *");
        source.print  ("     * @param "); source.print(valueName); source.println(" - the value of the AVP");
        source.println("     */");
    }

    // Command Constructor Documents

    public static void generateForCommandConstructor(PrintWriter source, String className) {
        source.println("    /**");
        source.print  ("     * Constructs a new "); source.print(className); source.println(" command.");
        source.println("     *");
        source.println("     * @param error - whether this command carries an error indicator");
        source.println("     * @param retrans - whether this is a retransmission");
        source.println("     */");
    }

    public static void generateForCommandConstructor(PrintWriter source, String className, String genericName) {
        source.println("    /**");
        source.print  ("     * Constructs a "); source.print(className); source.println(" command from a GenericCommand.");
        source.println("     *");
        source.print  ("     * @param "); source.print(genericName); source.println(" - the GenericCommand");
        source.println("     */");
    }

    public static void generateForCommandConstructor(PrintWriter source, String className, String bufferName, String lengthName) {
        source.println("    /**");
        source.print  ("     * Constructs a "); source.print(className); source.println(" command by decoding a byte array.");
        source.println("     *");
        source.print  ("     * @param "); source.print(bufferName); source.println(" - the buffer that contains the encoded bytes");
        if (lengthName != null) {
            source.print("     * @param "); source.print(lengthName); source.println(" - the length of the buffer");
        }
        source.println("     */");
    }

    // Named Accessor Documents

    public static void generateForGetter(PrintWriter source, String attributeName, String indexName) {
        String article = indexName != null ? "one " : "the ";
        source.println("    /**");
        source.print  ("     * Gets "); source.print(article); source.print(attributeName); source.println('.');
        if (indexName != null) {
            source.println("     *");
            source.print  ("     * @param "); source.print(indexName); source.println(" - the index of the attribute to return");
        }
        source.println("     */");
    }

    public static void generateForTester(PrintWriter source, String attributeName) {
        source.println("    /**");
        source.print  ("     * Tests whether there is any "); source.print(attributeName); source.println('.');
        source.println("     */");
    }

    public static void generateForCounter(PrintWriter source, String attributeName) {
        source.println("    /**");
        source.print  ("     * Returns number of "); source.print(attributeName); source.println(" instances.");
        source.println("     */");
    }

    public static void generateForSetter(PrintWriter source, String attributeName, String valueName, boolean single) {
        String verb = single ? "Sets the " : "Adds one ";

        source.println("    /**");
        source.print  ("     * "); source.print(verb); source.print(attributeName); source.println('.');
        source.println("     *");
        source.print  ("     * @param "); source.print(valueName); source.println(" - the attribute value");
        source.println("     */");
    }

    // Any Accessor Documents

    public static void generateForAnyGetter(PrintWriter source, String attributeName, String indexName) {
        source.println("    /**");
        source.println("     * Gets an extra AVP that matches the given attribute name.");
        source.println("     *");
        source.print  ("     * @param "); source.print(attributeName); source.println(" - the attribute to return");
        if (indexName != null) {
            source.print  ("     * @param "); source.print(indexName); source.println(" - the index of the attribute to return");
        }
        source.println("     */");
    }

    public static void generateForAnyTester(PrintWriter source, String attributeName) {
        source.println("    /**");
        source.print  ("     * Tests whether there is any extra AVP");
        if (attributeName != null) {
            source.println(" that matches the given attribute name.");
            source.println("     *");
            source.print  ("     * @param "); source.print(attributeName); source.println(" - the attribute to return");
        } else {
            source.println('.');
        }
        source.println("     */");
    }

    public static void generateForAnyCounter(PrintWriter source, String attributeName) {
        source.println("    /**");
        source.print  ("     * Returns number of extra AVP instances");
        if (attributeName != null) {
            source.println(" that match the given attribute name.");
            source.println("     *");
            source.print  ("     * @param "); source.print(attributeName); source.println(" - the attribute to count");
        } else {
            source.println('.');
        }
        source.println("     */");
    }

    public static void generateForAnySetter(PrintWriter source, String valueName, boolean single) {
        String verb = single ? "Sets the " : "Adds one ";

        source.println("    /**");
        source.print  ("     * "); source.print(verb); source.println("extra AVP.");
        source.println("     *");
        source.print  ("     * @param "); source.print(valueName); source.println(" - the attribute value");
        source.println("     */");
    }
}
