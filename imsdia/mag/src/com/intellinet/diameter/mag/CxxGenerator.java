/*******************************-*CPP-*-*************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *
 *  LOG: $Log: CxxGenerator.java,v $
 *  LOG: Revision 3.2.20.9.4.1  2013/02/27 04:48:32  millayaraja
 *  LOG: modified for interface stats
 *  LOG:
 *  LOG: Revision 3.2.20.9  2012/12/21 05:44:24  ncshivakumar
 *  LOG: modified for tracing
 *  LOG:
 *  LOG: Revision 3.2.20.8  2012/10/03 15:09:57  cprem
 *  LOG: Merged from ERLBF branch B-DRE-0212-02
 *  LOG:
 *  LOG: Revision 3.2.20.5.2.1  2012/09/14 15:41:08  cprem
 *  LOG: Added code to generate information required for generic AVP access.
 *  LOG:*/

package com.intellinet.diameter.mag;

import java.io.*;
import java.util.*;

import com.intellinet.diameter.mag.analysis.*;
import com.intellinet.diameter.mag.node.*;
import com.intellinet.diameter.mag.util.*;


public class CxxGenerator {

    private String _dictFile = "dictInfo.txt";

    public CxxGenerator(String pathname) {
        /*
           int hash = pathname.indexOf('%');
           if (hash > 0) {
           validate(_hdrRoot = new File(pathname.substring(0, hash)));
           validate(_srcRoot = new File(pathname.substring(hash+1)));
           } else {
           validate(_hdrRoot = _srcRoot = new File(pathname));
           }
           */
        validate(_hdrRoot = new File(pathname, "include"));
        validate(_srcRoot = new File(pathname, "src"));
        validate(_tstRoot = new File(pathname, "test"));

        /*System.out.println("ROOT DIRECTORY");
          System.out.println(_hdrRoot);*/
    }

    /**
     * Processes one protocol/application. This method is to be called many times, once for each diameter application.
     * @throws Exception 
     */
    public void process(SemanticAnalyzer analyzer) throws Exception {
        String fs = System.getProperty("file.separator");
        _protocolId = analyzer.getGrammar().getId().getText();
        _namespaces = analyzer.getAllNamespaces();

        //Added for DTF
        TInteger dictId = analyzer.getGrammar().getDictId();
        if(dictId != null)
        {
            _dictId = analyzer.getGrammar().getDictId().getText();
        } else {
            _dictId = null;
        }
        //End of Addition for DTF

        String[] myNamespace = _namespaces[_namespaces.length - 1];
        StringBuffer path = new StringBuffer(myNamespace[0]);
        for (int i = 1; i < myNamespace.length; ++i) {
            path.append(fs).append(myNamespace[i]);
        }
        _protocolName = capitalize(myNamespace[myNamespace.length-1]);
        validate(_hdrDirectory = new File(_hdrRoot, path.toString()));
        validate(_srcDirectory = new File(_srcRoot, path.toString()));
        validate(_tstDirectory = new File(_tstRoot, path.toString()));

        processAvps(analyzer);
        processCommands(analyzer);


        /*Prem:Code Generation for Dictionary Classes. 
         * The Diameter Transformer Function would use these dictionary classes.
         * Don't generate dictionary classes for base protocols.*/

        if ((_dictId !=null) && !(_dictId.trim().equals("0"))) {
            if(checkForDuplicateDictId() == false)
            {
                generateDiameterDictionary(analyzer);
                addDictIdtoDictFile();
            }else {
                throw new Exception("Duplicate Dictionary Id's found, dict id:" + _dictId);
            }
        }



    }
    private void addDictIdtoDictFile() throws IOException{

        FileWriter file = new FileWriter(_srcRoot +"/" +_dictFile,true);
        file.append(_dictId + "\n");
        file.close();
    }

    private boolean checkForDuplicateDictId() throws IOException {

        File file = new File(_srcRoot,_dictFile);
        FileReader fr = new FileReader(file);

        BufferedReader br = new BufferedReader(fr);
        br.readLine();
        String token;
        while((token = br.readLine())!=null)
        {
            token.replace(",", "");
            token.trim();
            if(token.equals(_dictId))
            {
                fr.close();
                br.close();
                return true;
            }
        }
        fr.close();		
        return false;
    }    

    /*Prem: Code Generation for Dictionary Classes.
     * */
    private void generateDiameterDictionary(SemanticAnalyzer analyzer) throws IOException{

        String DictClsName =  _protocolName.replaceAll("_", "").toUpperCase() + "Dictionary" ;


        //Get the Application Id
        Map.Entry<String, CommandPair> entry = analyzer.getCommands().entrySet().iterator().next();
        CommandPair cmdPair = entry.getValue();
        String appId = cmdPair.appId.getText(); 

        File file = new File(_hdrDirectory, DictClsName + ".h");
        PrintWriter header = new PrintWriter(new FileWriter(file));

        file = new File(_srcDirectory, DictClsName + ".cpp");
        PrintWriter source = new PrintWriter(new FileWriter(file));

        //Start of Dictionary Header file
        header.println("#ifndef _" + _protocolName.toUpperCase() + "_DICTIONARY_H_");
        header.println("#define _" + _protocolName.toUpperCase() + "_DICTIONARY_H_");
        openNamespaces(header, _namespaces[_namespaces.length - 1]);

        //Generate Typedef's for map and pair

        header.println("");

        header.println("    typedef std::pair<const diameter::CommandAttribute*,const diameter::CommandAttribute*> CommandAttributePair;");
        header.println("    typedef std::unordered_map<int64_t,CommandAttributePair> CommandAttributeMap;");

        header.println("");

        //Generate the Dictionary Class Declaration and Constructor definition.
        header.print("class "); header.print(DictClsName); header.println(": public diameter::DiameterDictionary {");
        header.println("");
        header.println("public:");
        //Start of Constructor
        header.print("    " + DictClsName + "()");header.println(": diameter::DiameterDictionary(\"" + _dictName + "\","+ appId +","+ _dictId +") {");

        String pairName = "";
        int commandCode = 0;
        String reqAttr = "";
        String ansAttr = "";		
        String cmdName = "";
        String clsName = "";

        //Code to initialize CommandAttributePair Map and DictionaryStatsMap.

        for (Map.Entry<String, CommandPair> entry1: analyzer.getCommands().entrySet()) {

            CommandPair pair = entry1.getValue();
            clsName = pair.name.replaceAll("-", "");
            cmdName = pair.req.getName().getText().replaceAll("-", "");
            reqAttr = clsName+ "Attribute::" + cmdName;
            cmdName = pair.res.getName().getText().replaceAll("-", "");
            ansAttr = clsName+ "Attribute::" + cmdName;
            commandCode = pair.code;
            pairName = clsName + "Pair";

            header.println("        CommandAttributePair " + pairName + "( &(" + reqAttr + "),");
            header.println("          &(" + ansAttr + "));");
            header.println("");
            header.println("        attributeMap[" + commandCode + "] = " + pairName + ";");
            header.println("");
            header.println("        DictStatsMap[" + commandCode + "] = new DiameterDictionaryStats();");
            header.println("");
        }
        header.println("    }");

        //End of Constructor


        header.println("");
        header.println("    diameter::Command* createCommandObject(unsigned int CommandCode,const diameter::CommandImpl& impl);");
        header.println("    diameter::Command* createCommandObject(unsigned int CommandCode,bool isRequest);");
        header.println("    diameter::Command* createCommandObject(const unsigned char* buf,int len);");
        header.println("    const diameter::CommandAttribute* getCommandAttribute(unsigned int CommandCode,bool isRequest);");

        header.println("");
        header.println("private:");
        header.println("    CommandAttributeMap attributeMap;");

        header.println("};");
        closeNamespaces(header, _namespaces[_namespaces.length - 1]);
        //End of Dictionary Header file
        header.println("#endif");

        header.close();

        //Dictionary Source File.
        source.println("#include <unordered_map>");
        source.println("#include <string>");
        source.println("#include <stdbool.h>");
        source.println("#include <PluginObj.h>");
        source.println("#include <diameter/Command.h>");
        source.println("#include <DiameterDictionary.h>");
        source.println("#include <DiameterDictionaryStats.h>");
        source.println("#include <diameter/base/BaseGenericCommand.h>");


        printCommandIncludes(source,analyzer);

        source.print("#include <");
        printPathForInclude(source);
        source.print(DictClsName); source.println(".h>");

        openNamespaces(source, _namespaces[_namespaces.length - 1]);

        //CreateCommandObj Implementation
        //Start of createCommandObject(unsigned int CommandCode,const diameter::CommandImpl& impl) function definition
        source.println("    diameter::Command* "+ DictClsName + "::createCommandObject(unsigned int CommandCode,const diameter::CommandImpl& impl) {");
        source.println("        if(impl.isRequest()) {");
        source.println("            switch(CommandCode) {");

        printCommandSelection(source,analyzer,"        ","impl",true);

        source.println("            }");
        source.println("        } else {");
        source.println("            switch(CommandCode) {");

        printCommandSelection(source,analyzer,"        ","impl",false);

        source.println("            }");
        source.println("        }");
        source.println("    }");
        //End of createCommandObject(unsigned int CommandCode,const diameter::CommandImpl& impl) function definition

        //Start of createCommandObject(unsigned int CommandCode,bool isRequest) function definition
        source.println("    diameter::Command* "+ DictClsName + "::createCommandObject(unsigned int CommandCode,bool isRequest) {");
        source.println("        if(isRequest) {");
        source.println("            switch(CommandCode) {");

        printCommandSelection(source,analyzer,"        ","",true);

        source.println("            }");
        source.println("        } else {");
        source.println("            switch(CommandCode) {");

        printCommandSelection(source,analyzer,"        ","",false);

        source.println("            }");
        source.println("        }");
        source.println("    }");
        //End of createCommandObject(unsigned int CommandCode,bool isRequest) function definition

        //Start of createCommandObject(const unsigned char* buf,int len) function definition
        source.println("    diameter::Command* "+ DictClsName + "::createCommandObject(const unsigned char* buf,int len) {");
        source.println("    diameter::Command* cmd = new diameter::base::BaseGenericCommand(buf,len);");
        source.println("    const diameter::CommandImpl& impl = cmd->getImpl();");
        source.println("        if(impl.isRequest()) {");
        source.println("            switch(impl.getCommandCode()) {");

        printCommandSelection(source,analyzer,"        ","impl",true);

        source.println("            }");
        source.println("        } else {");
        source.println("            switch(impl.getCommandCode()) {");

        printCommandSelection(source,analyzer,"        ","impl",false);

        source.println("            }");
        source.println("        }");
        source.println("    }");
        //End of createCommandObject(const unsigned char* buf,int len) function definition

        //Start of getCommandAttribute function definition
        source.println("    const diameter::CommandAttribute* "+ DictClsName + 
                "::getCommandAttribute(unsigned int commandCode, bool isRequest){ ");
        source.println("");
        source.println("         CommandAttributeMap::iterator it = attributeMap.find(commandCode);");
        source.println("         	if(it == attributeMap.end()) {");
        source.println("         	    return NULL;");
        source.println("            }");		
        source.println("            else {");
        source.println("                CommandAttributePair attributePair = it->second;");
        source.println("                if(isRequest) {");
        source.println("                    return attributePair.first;");
        source.println("                }");
        source.println("                else {");
        source.println("                    return attributePair.second;");
        source.println("                }");
        source.println("            }");
        source.println("    }");
        //End of getCommandAttribute function definition

        closeNamespaces(source, _namespaces[_namespaces.length - 1]);

        source.println("");

        //Generate CreatePlugin function based on Dictionary Name.		
        source.println("extern \"C\" eAccelero::PluginObject* " + _dictName + "_CreatePlugin(std::string pluginType) {");
        source.print("    return new "); printNamespaces(source, _namespaces[_namespaces.length - 1]); 
        source.println(DictClsName + "();");
        source.println("}");

        source.close();
    }

    private void printCommandIncludes(PrintWriter pw,
            SemanticAnalyzer analyzer) {
        String cmdName;
        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet()) {
            CommandPair pair = entry.getValue();
            cmdName = pair.name.replaceAll("-", "");
            pw.print("#include <"); printPathForInclude(pw); pw.print(cmdName);pw.println(".h>");			
        }

    }	

    private void printPathForInclude(PrintWriter pw) {
        for (int i = 0; i < _namespaces[_namespaces.length - 1].length; ++i) {
            pw.print(_namespaces[_namespaces.length - 1][i]); pw.print('/');
        }
    }

    private void printCommandSelection(PrintWriter source,
            SemanticAnalyzer analyzer, String startIndent,String args,boolean isRequest) {
        String clsName;
        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet()) {
            CommandPair pair = entry.getValue();
            if(isRequest) {	
                clsName = pair.req.getName().getText().replaceAll("-", "");
            }else {
                clsName = pair.res.getName().getText().replaceAll("-", "");
            }
            source.println(startIndent + "        case " + pair.code + ":");
            source.print(startIndent + "            return new "); printNamespaces(source, _namespaces[_namespaces.length - 1]);
            source.println(clsName + "(" + args + ");");
            source.println(startIndent + "            break;");
        }
        source.println(startIndent + "        default:");
        source.println(startIndent + "            throw WrongCommandTypeException(__FILE__, __LINE__, \"Invalid Command Code for Dictionary.\");");
        source.println(startIndent + "            break;");

    }

    public void process(SemanticAnalyzer analyzer,SemanticAnalyzer analyzer1) throws IOException {
        String fs = System.getProperty("file.separator");

        _protocolId = analyzer.getGrammar().getId().getText();
        _namespaces = analyzer.getAllNamespaces();
        String[] myNamespace = _namespaces[_namespaces.length - 1];

        _protocolId1 = analyzer1.getGrammar().getId().getText();
        _namespaces1 = analyzer1.getAllNamespaces();
        String[] myNamespace1 = _namespaces1[_namespaces1.length - 1];

        StringBuffer path = new StringBuffer(myNamespace[0]);
        for (int i = 1; i < myNamespace.length; ++i) {
            path.append(fs).append(myNamespace[i]);
        }
        _protocolName = myNamespace[myNamespace.length-1];
        _protocolName1 = myNamespace1[myNamespace1.length-1];

        //Generate Transformer Classes
        generateDiameterTransformer(analyzer,analyzer1);			     

    }

    private void generateTransformerCopyClass(SemanticAnalyzer analyzer,SemanticAnalyzer analyzer1,File srcDir,String clsName, String transformHeaderIncl) throws IOException {

        String Filename = "DTFCopyMethodFor" + _protocolName + "And" + _protocolName1 + ".cpp";

        String Filename1 = "DTFFunctionsFor" + _protocolName + "And" + _protocolName1 + ".cpp";

        File file = new File(srcDir, Filename);
        PrintWriter source1 = new PrintWriter(new FileWriter(file,false));

        File file1 = new File(srcDir, Filename1);
        PrintWriter source2 = new PrintWriter(new FileWriter(file1,false));

        printIncludesForCopyMethods(source1,analyzer,analyzer1);
        source1.println(transformHeaderIncl);
        openNamespacesforTransformer(source1);

        printIncludesForCopyMethods(source2,analyzer,analyzer1);
        source2.println(transformHeaderIncl);
        openNamespacesforTransformer(source2);

        processCommandsForCopy(source1,source2,analyzer,analyzer1,clsName);

        closeNamespacesforTransformer(source1);
        closeNamespacesforTransformer(source2);

        source1.close();
        source2.close();
    }

    private void printCommonIncludesForTransformer(PrintWriter source)
    {
        source.println("#include <DTFLog.h>");
        source.println("#include <json/json.h>");	
        source.println("#include <dia_cmn.h>");		
        source.println("#include <dia_msg_flow.h>");
        source.println("#include <Sync.h>");
        source.println("#include <PluginObj.h>");
        source.println("#include <DiameterTransformer.h>");
    }


    private String removeDebugSuffix(String input)
    {
        if(input.endsWith("D"))
        {
            input = input.substring(0, input.length()-1);
        }
        return input;
    }

    /*Prem: Code Generation for Transformer Classes.
     * */
    private void generateDiameterTransformer(SemanticAnalyzer analyzer,SemanticAnalyzer analyzer1) throws IOException {

        //Transformer Plugin generation
        String fs = System.getProperty("file.separator");
        String TransformerClsName = null;

        //Initialize NameSpaces
        _transformerNamespaces = new String[2];

        _transformerNamespaces[0] = "diameter";
        _transformerNamespaces[1] = removeDebugSuffix(pluginName);

        String _dtfDirInclude = "diameter" + fs + "transform" + fs +removeDebugSuffix(pluginName);
        validate(_dtfhdrDirectory = new File(_hdrRoot,_dtfDirInclude));
        String FilePrefix = removeDebugSuffix(pluginName.replaceAll("_", ""));				

        String hdrFileName = "Diameter" + FilePrefix +".h";
        String srcFileName = "Diameter" + FilePrefix +".cpp";
        File file = new File(_dtfhdrDirectory,hdrFileName);
        PrintWriter header = new PrintWriter(file);

        validate(_dtfsrcDirectory = new File(_srcRoot,_dtfDirInclude));
        File file1 = new File(_dtfsrcDirectory,srcFileName);
        PrintWriter source = new PrintWriter(file1);

        //Start of Transformer Header file
        header.println("#ifndef _" + removeDebugSuffix(pluginName).toUpperCase() + "_H_");
        header.println("#define _" + removeDebugSuffix(pluginName).toUpperCase() + "_H_");

        TransformerClsName = "Diameter" + FilePrefix;

        String transformHeaderIncl = "#include <" + _dtfDirInclude + fs + hdrFileName + ">";

        //Generate Copy Methods
        generateTransformerCopyClass(analyzer,analyzer1,_dtfsrcDirectory,TransformerClsName,transformHeaderIncl);

        header.println("");
        openNamespacesforTransformer(header);
        header.println("");

        //Generate Transformer Class Declaration
        header.print("class "); header.print(TransformerClsName); header.println(": public diameter::DiameterTransformer {");
        header.println("");
        header.println("public:");
        header.print("    " + TransformerClsName + "()");header.println(": diameter::DiameterTransformer(\"" + pluginName +"\") {}");
        header.println("");

        header.println("    void transform(diameter::DiaMsgFlow& inMsg, unsigned int outDictId, diameter::DiaMsgFlow** outMsg);\n");
        header.println("    void Initialize();\n");
        header.println("    int Configure(void* conf);\n");
        header.println("    void Terminate();\n");

        header.println("");
        header.println("private:");

        printCopyandConfigureMethodDecls(header,analyzer,analyzer1,"    ");

        header.println("};");
        closeNamespacesforTransformer(header);
        header.println("#endif");
        header.close();

        /*		source.println("#include <string>");
                source.println("#include <json/json.h>");
                source.println("#include <dia_cmn.h>");		
                source.println("#include <Sync.h>");
                source.println("#include <dia_msg_flow.h>");
                source.println("#include <PluginObj.h>");		
                source.println("#include <DiameterTransformer.h>");	*/	

        printIncludesForCopyMethods(source,analyzer,analyzer1);
        source.println(transformHeaderIncl);

        openNamespacesforTransformer(source);

        source.print("void " + TransformerClsName); 
        source.println("::transform(diameter::DiaMsgFlow& inMsg, unsigned int outDictId, diameter::DiaMsgFlow** outMsg) {");
        source.println("");
        source.println("        unsigned int CommandCode = inMsg.getCommandCode();");

        source.println("        if(inMsg.isRequest()) {");
        source.println("            switch(CommandCode) {");

        printCommandCopySelection(source,analyzer,analyzer1,"        ","",true);

        source.println("            }");
        source.println("        } else {");
        source.println("            switch(CommandCode) {");

        printCommandCopySelection(source,analyzer,analyzer1,"        ","",false);

        source.println("            }");

        source.println("        }");		

        source.println("}\n");

        source.print("void " + TransformerClsName); 
        source.println("::Initialize() {");

        source.println("}\n");

        source.print("int " + TransformerClsName); 
        source.println("::Configure(void* conf) {");
        source.println("    return 0;");
        source.println("}\n");

        source.print("void " + TransformerClsName); 
        source.println("::Terminate() {");

        source.println("}\n");

        closeNamespacesforTransformer(source);
        source.println("\n");

        //Generate CreatePlugin function based on Dictionary Name.
        source.println("extern \"C\" eAccelero::PluginObject* " + pluginName + "_CreatePlugin(std::string pluginType) {");
        source.print("    return new "); printNamespacesforTransformer(source); 
        source.println(TransformerClsName + "();");
        source.println("}");

        source.close();
    }

    private void printCopyandConfigureMethodDecls(PrintWriter source,
            SemanticAnalyzer analyzer, SemanticAnalyzer analyzer1,String startIndent) {

        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet())
        {
            CommandPair pair = entry.getValue();
            String clsName = pair.name.replaceAll("-", "");
            if (pair.req != null) 
            {
                source.println("");
                source.print(startIndent + "void ");
                printCopyMethodForTransformer(source,clsName,_protocolName,_protocolName1,true);
                source.print("( ");

                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Request");source.print(" &fromMsg ,");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);
                source.print(clsName);source.print("Request");source.println(" &toMsg );");

                source.println("");
                source.print(startIndent + "void ");
                printFillMethodForTransformer(source,clsName,_protocolName,_protocolName1,true);
                source.print("( ");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);
                source.print(clsName);source.print("Request");source.println(" &toMsg );");

                //Configure Method Declaration.
                source.println("");
                source.print(startIndent + "void ");
                printConfigureMethodForTransformer(source,clsName,_protocolName,_protocolName1,true);
                source.print("(Json::Value* cfg);");

            }
            if (pair.res != null)
            {
                source.println("");
                source.print(startIndent + "void ");
                printCopyMethodForTransformer(source,clsName,_protocolName,_protocolName1,false);
                source.print("( ");
                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Answer");source.print(" &fromMsg ,");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);
                source.print(clsName);source.print("Answer");source.println(" &toMsg );");

                source.println("");
                source.print(startIndent + "void ");
                printFillMethodForTransformer(source,clsName,_protocolName,_protocolName1,false);
                source.print("( ");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);
                source.print(clsName);source.print("Answer");source.println(" &toMsg );");

                //Configure Method Declaration.
                source.println("");
                source.print(startIndent + "void ");
                printConfigureMethodForTransformer(source,clsName,_protocolName,_protocolName1,false);
                source.print("(Json::Value* cfg);");


            }

        }
        for (Map.Entry<String, CommandPair> entry: analyzer1.getCommands().entrySet())
        {
            CommandPair pair = entry.getValue();
            String clsName = pair.name.replaceAll("-", "");			
            if (pair.req != null) 
            {
                source.println("");
                source.print(startIndent + "void ");
                printCopyMethodForTransformer(source,clsName,_protocolName1,_protocolName,true);
                source.print("(");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);
                source.print(clsName);source.print("Request");source.print(" &fromMsg ,");
                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Request");source.println(" &toMsg );");

                source.println("");
                source.print(startIndent + "void ");
                printFillMethodForTransformer(source,clsName,_protocolName1,_protocolName,true);
                source.print("( ");
                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Request");source.println(" &toMsg );");


                //Configure Method Declaration.
                source.println("");
                source.print(startIndent + "void ");
                printConfigureMethodForTransformer(source,clsName,_protocolName1,_protocolName,true);
                source.print("(Json::Value* cfg);");

            }
            if (pair.res != null)
            {
                source.println("");
                source.print(startIndent + "void ");
                printCopyMethodForTransformer(source,clsName,_protocolName1,_protocolName,false);
                source.print("(");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);
                source.print(clsName);source.print("Answer");source.print(" &fromMsg ,");
                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Answer");source.println(" &toMsg );");

                source.println("");
                source.print(startIndent + "void ");
                printFillMethodForTransformer(source,clsName,_protocolName1,_protocolName,false);
                source.print("( ");
                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Answer");source.println(" &toMsg );");

                //Configure Method Declaration.
                source.println("");
                source.print(startIndent + "void ");
                printConfigureMethodForTransformer(source,clsName,_protocolName1,_protocolName,false);
                source.print("(Json::Value* cfg);");
            }
        }	
        source.println("");
    }

    private void printCommandObjCreation(PrintWriter pw, CommandPair pair, String namespaces[] ,
            String namespaces1[],boolean isRequest,String startIndent) {

        pw.print(startIndent);
        printNamespaces(pw, namespaces);
        if(isRequest)
        {
            pw.print(pair.req.getName().getText().replaceAll("-", ""));
        }
        else
        {
            pw.print( pair.res.getName().getText().replaceAll("-", ""));
        }
        pw.println(" inCmd( bGenCmd->getImpl() );");

        pw.print(startIndent);
        printNamespaces(pw, namespaces1);
        if(isRequest)
        {
            pw.print(pair.req.getName().getText().replaceAll("-", ""));
        }
        else
        {
            pw.print(pair.res.getName().getText().replaceAll("-", ""));
        }
        pw.println(" outCmd(inCmd.isError(),inCmd.isRetransmit(),inCmd.isProxyable());");
    }

    private void printCommandCopySelection(PrintWriter source,
            SemanticAnalyzer analyzer, SemanticAnalyzer analyzer1, String startIndent,String args, boolean isRequest) {

        String clsName;
        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet()) {
            CommandPair pair = entry.getValue();
            clsName = pair.name.replaceAll("-", "");			
            source.println(startIndent + "        case " + pair.code + ":");
            source.println(startIndent + "        {");
            source.println(startIndent + "            diameter::base::BaseGenericCommand* bGenCmd = inMsg.GetBaseGenCommand();");

            source.println("");
            //In indict Matches dict1
            source.println(startIndent + "            if(inMsg.GetDictId() == " + 
                    analyzer.getGrammar().getDictId().getText() + ") {");
            source.println(startIndent + "                DTF_DBG((\"inMSg CommandCode %d, isRequest %d.\",bGenCmd->getImpl().getCommandCode(),inMsg.isRequest()));");

            printCommandObjCreation(source,pair,_namespaces[_namespaces.length-1],_namespaces1[_namespaces1.length-1],
                    isRequest,startIndent + "                ");

            source.print(startIndent + "                ");
            printCopyMethodForTransformer(source,clsName,_protocolName,_protocolName1,isRequest);
            source.println("( inCmd , outCmd );");

            source.println(startIndent + "                diameter::base::BaseGenericCommand* cmd = new diameter::base::BaseGenericCommand(const_cast<diameter::CommandImpl&>(outCmd.getImpl()));");
            source.println(startIndent + "                *outMsg = new DiaMsgFlow(cmd);");
            source.println(startIndent + "                (*outMsg)->SetDictId(outDictId);");
            source.println(startIndent + "            }");

            source.println(startIndent + "            else if(inMsg.GetDictId() == " + 
                    analyzer1.getGrammar().getDictId().getText() + ") {");

            source.println(startIndent + "                DTF_DBG((\"inMSg CommandCode %d, isRequest %d.\",bGenCmd->getImpl().getCommandCode(),inMsg.isRequest()));");

            printCommandObjCreation(source,pair,_namespaces1[_namespaces1.length-1],_namespaces[_namespaces.length-1],
                    isRequest,startIndent + "                ");

            source.print(startIndent + "                ");
            printCopyMethodForTransformer(source,clsName,_protocolName1,_protocolName,isRequest);
            source.println("( inCmd , outCmd );");

            source.println(startIndent + "                diameter::base::BaseGenericCommand* cmd = new diameter::base::BaseGenericCommand(const_cast<diameter::CommandImpl&>(outCmd.getImpl()));");

            source.println(startIndent + "                 DTF_DBG((\"outCmd outCmd.CommandCode %d.\",outCmd.getCommandCode()));");
            source.println(startIndent + "                *outMsg = new DiaMsgFlow(cmd);");
            source.println(startIndent + "                (*outMsg)->SetDictId(outDictId);");
            source.println(startIndent + "            }");

            source.println(startIndent + "            else {");
            source.println(startIndent + "                DTF_ERR((\"Dictionary Id's doesn't match.\"));");
            source.println(startIndent + "                return;");
            source.println(startIndent + "            }");


            source.println(startIndent + "            return ;");						
            source.println(startIndent + "            break;");
            source.println(startIndent + "        }");
        }

        source.println(startIndent + "        default:");
        source.println(startIndent + "        {");
        source.println(startIndent + "            throw WrongCommandTypeException(__FILE__, __LINE__, \"Invalid Command Code for Transformation.\");");
        source.println(startIndent + "            break;");
        source.println(startIndent + "        }");
    }



    private void closeNamespacesforTransformer(PrintWriter pw) {
        pw.println();
        for (int i = _transformerNamespaces.length-1; i >= 0; --i) {
            pw.print("} /*"); pw.print(_transformerNamespaces[i]); pw.print("*/ ");
        }
        pw.println();
    }



    private void openNamespacesforTransformer(PrintWriter pw) {

        pw.println();
        for (int i = 0; i < _transformerNamespaces.length; ++i) {
            pw.print("namespace " + _transformerNamespaces[i] + " { ");
        }
        pw.println();
        pw.println();
    }



    private void printNamespacesforTransformer(PrintWriter pw) {

        for (int i = 0; i < _transformerNamespaces.length; ++i) {
            pw.print(_transformerNamespaces[i] + "::");
        }	

    }

    private void printCopyMethodForTransformer(PrintWriter pw,String clsName,String fromIntf,String toIntf,boolean isRequest)
    {
        pw.print("Copy"); pw.print(clsName);
        if(isRequest)
        {
            pw.print("RequestFrom");	
        }else {
            pw.print("AnswerFrom");
        }			
        pw.print(fromIntf);
        pw.print("_To");pw.print(toIntf);
    }

    private void printFillMethodForTransformer(PrintWriter pw,String clsName,String fromIntf,String toIntf,boolean isRequest)
    {
        pw.print("FillNewAVPs"); pw.print(clsName);
        if(isRequest)
        {
            pw.print("RequestFrom");	
        }else {
            pw.print("AnswerFrom");
        }			
        pw.print(fromIntf);
        pw.print("_To");pw.print(toIntf);
    }


    private void printConfigureMethodForTransformer(PrintWriter pw,String clsName,String fromIntf,String toIntf,boolean isRequest)
    {
        pw.print("ConfigureNewAVPs"); pw.print(clsName);
        if(isRequest)
        {
            pw.print("RequestFrom");	
        }else {
            pw.print("AnswerFrom");
        }			
        pw.print(fromIntf);
        pw.print("_To");pw.print(toIntf);
    }


    private final File _hdrRoot, _srcRoot, _tstRoot;

    private File _hdrDirectory, _srcDirectory, _tstDirectory,_dtfDirectory,_dtfsrcDirectory,_dtfhdrDirectory;
    private String[][] _namespaces;
    private String _protocolName;
    private String _protocolId;

    //Added for DTF
    private String[][] _namespaces1;
    private String _protocolName1;
    private String _protocolId1;
    private String pluginName;
    private String[] _transformerNamespaces;	
    private String _dictName;
    private String _dictId;

    /**
     * @return the _dictId
     */
    public String get_dictId() {
        return _dictId;
    }

    /**
     * @param _dictId the _dictId to set
     */
    public void set_dictId(String _dictId) {
        this._dictId = _dictId;
    }

    /**
     * @return the _dictName
     */
    public String get_dictName() {
        return _dictName;
    }

    /**
     * @param _dictName the _dictName to set
     */
    public void set_dictName(String _dictName) {
        this._dictName = _dictName;
    }

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

    private static final void openNamespaces(PrintWriter pw, String[] name) {
        pw.println();
        for (int i = 0; i < name.length; ++i) {
            pw.print("namespace " + name[i] + " { ");
        }
        pw.println();
        pw.println();
    }

    private static final void closeNamespaces(PrintWriter pw, String[] name) {
        pw.println();
        for (int i = name.length-1; i >= 0; --i) {
            pw.print("} /*"); pw.print(name[i]); pw.print("*/ ");
        }
        pw.println();
    }

    private static final void printNamespaces(PrintWriter pw, String[] name) {
        for (int i = 0; i < name.length; ++i) {
            pw.print(name[i] + "::");
        }
    }

    private static final String[] printNamespaces(PrintWriter pw, SemanticAnalyzer analyzer, String avp) {
        AGrammar grammar = analyzer.getGrammarForAvp(avp);
        String[] namespaces = SemanticAnalyzer.getNamespaces(grammar);
        if (grammar != analyzer.getGrammar()) {
            for (int i = 0; i < namespaces.length; ++i) {
                pw.print(namespaces[i]);
                pw.print("::");
            }
        }
        return namespaces;
    }

    private static final void printAvpIncludes(PrintWriter pw, String[][] names) {
        for (int i = 0; i < names.length; ++i) {
            pw.print("#include <");
            for (int j = 0; j < names[i].length; ++j) {
                pw.print(names[i][j]); pw.print('/');
            }
            pw.print(capitalize(names[i][names[i].length - 1])); pw.println("AVP.h>");
        }
    }

    private static final void printDerivedClassName(PrintWriter pw, PAvpType avpType) {
        String type = OpenDiameterUtil.getCxxTypeName(avpType);
        pw.print("DerivedAVP<");
        pw.print(type);
        pw.print(", ");
        pw.print(type);
        pw.print("Type");
        pw.print('>');
    }

    private static final void printAttributeNamespace(PrintWriter pw, SemanticAnalyzer analyzer, String name) {
        String[] namespaces = printNamespaces(pw, analyzer, name);
        pw.print(capitalize(namespaces[namespaces.length - 1]));
        pw.print("AttributeName::");
    }

    private static final void printAttributeName(PrintWriter pw, SemanticAnalyzer analyzer, String name) {
        String[] namespaces = printNamespaces(pw, analyzer, name);
        pw.print(capitalize(namespaces[namespaces.length - 1]));
        pw.print("AttributeName::"); pw.print(name.replaceAll("-", ""));
    }

    private static final void printAttributeType(PrintWriter pw, SemanticAnalyzer analyzer, String name) {
        String[] namespaces = printNamespaces(pw, analyzer, name);
        pw.print(capitalize(namespaces[namespaces.length - 1]));
        if (analyzer.getGroupedAVPs().get(name) != null) {
            pw.print(name.replaceAll("-", "")); pw.print("Name");
        } else {
            pw.print("AttributeName");
        }
    }

    private final void printMemberAttributeName(PrintWriter pw, SemanticAnalyzer analyzer, String group, String attr) {
        if (analyzer.getGrammarForAvp(group) != null) { // grouped AVP
            String[] namespaces = printNamespaces(pw, analyzer, group);
            pw.print(capitalize(namespaces[namespaces.length - 1]));
            pw.print(group.replaceAll("-", "")); pw.print("Name::");
            pw.print(attr.replaceAll("-", ""));
        } else { // Command
            printAttributeName(pw, analyzer, attr);
        }
    }

    private static final void printTypeReference(PrintWriter pw, SemanticAnalyzer analyzer, String name) {
        printNamespaces(pw, analyzer, name);
        pw.print(name.replaceAll("-", ""));
    }


    private void processAvps(SemanticAnalyzer analyzer) throws IOException {
        boolean isBase = analyzer.getGrammar().getBase() != null;
        File file = new File(_hdrDirectory, _protocolName + "AVP.h");
        //System.err.println("Generating header file " + file.getCanonicalPath());
        PrintWriter header = new PrintWriter(new FileWriter(file));
        header.println("#ifndef _" + _protocolName + "AVP_H_");
        header.println("#define _" + _protocolName + "AVP_H_");
        header.println("#include <diameter/AVP.h>");
        openNamespaces(header, _namespaces[_namespaces.length - 1]);

        file = new File(_srcDirectory, _protocolName + "AVP.cpp");
        //System.err.println("Generating source file " + file.getCanonicalPath());
        PrintWriter source = new PrintWriter(new FileWriter(file));
        source.println("#include <diameter/Exceptions.h>");
        printAvpIncludes(source, _namespaces);
        openNamespaces(source, _namespaces[_namespaces.length - 1]);

        // Generate attribute names forward declarations
        header.print("class "); header.print(_protocolName); header.println("AttributeName;");
        header.println();

        // Generate grouped attribute names forward declarations
        for (Map.Entry<String, AGroupedDefinition> entry: analyzer.getGroupedAVPs().entrySet()) {
            AGroupedDefinition node = entry.getValue();
            String rfcName = node.getName().getText();
            String cppName = rfcName.replaceAll("-", "");
            header.print("class "); header.print(_protocolName); header.print(cppName); header.println("Name;");
        }
        header.println();

        // Generate AVP forward declarations
        for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
            generateAvpDeclarations(header, entry.getValue());
        }
        header.println();

        // Generate group attribute names declarations
        for (Map.Entry<String, AGroupedDefinition> entry: analyzer.getGroupedAVPs().entrySet()) {
            AGroupedDefinition node = entry.getValue();
            String rfcName = node.getName().getText();
            String cppName = rfcName.replaceAll("-", "");
            ADerivedDefinition definition = analyzer.getDerivedAVPs().get(rfcName);

            header.print("class ");
            header.print(_protocolName); header.print(cppName);
            header.print("Name: public GroupedAttributeName");
            if (isBase) {
                header.println(", public AttributeCodeMap {");
            } else {
                header.println(" {");
            }
            header.println("public:");
            header.print  ("    "); header.print(_protocolName); header.print(cppName);
            if(_protocolName.compareTo("Base") == 0)
            {
                header.println("Name(const char *n, const AvpBuilder &ap, const ImpBuilder &ip, unsigned avp, unsigned vendor = 0, bool mand = true, bool enc = true, bool base = true);");
            }
            else
            {
                header.println("Name(const char *n, const AvpBuilder &ap, const ImpBuilder &ip, unsigned avp, unsigned vendor = 0, bool mand = true, bool enc = true, bool base = false);");

            }

            AGroupedBody body = (AGroupedBody)node.getGroupedBody();
            generateGroupedAVPInfoDecl(header, analyzer, cppName, true, body.getFixed().iterator());
            generateGroupedAVPInfoDecl(header, analyzer, cppName, true, body.getRequired().iterator());
            generateGroupedAVPInfoDecl(header, analyzer, cppName, false, body.getOptional().iterator());
            header.println("};");
            header.println();
        }

        // Generate attribute names declarations
        DocumentWriter.generateForAttributeNames(source, _namespaces[_namespaces.length - 1][_namespaces[_namespaces.length - 1].length-1]);
        header.print("class "); header.print(_protocolName); header.print("AttributeName: public diameter::AttributeName");
        if (isBase) {
            header.println(", public diameter::AttributeCodeMap {");
        } else {
            header.println(" {");
        }
        header.println("public:");

        // Need to generate SessionId before any other attribute names
        List<ADerivedDefinition> avps = new ArrayList<ADerivedDefinition>();
        ADerivedDefinition sessionId = analyzer.getDerivedAVPs().get("Session-Id");
        if (sessionId != null) {
            avps.add(sessionId);
        }
        for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
            if (!entry.getKey().equals("Session-Id")) {
                avps.add(entry.getValue());
            }
        }

        for (ADerivedDefinition def: avps) {
            String rfcName = def.getName().getText();
            String cppName = rfcName.replaceAll("-", "");

            String mandatory = new AvpFlagSet((AAvpFlagRules)def.getAvpFlagRules()).getFlags()[AvpFlagSet.MANDATORY];

            header.print("    static struct "); header.print(cppName); header.println("AvpBuilder: public diameter::AvpBuilder {");
            header.println("        diameter::AVP *build(const diameter::AVPImpl *impl) const;");
            header.print  ("    } _"); header.print(cppName); header.println("AvpBuilder;");
            if (analyzer.getGroupedAVPs().get(rfcName) != null) {
                header.print("    static const "); header.print(_protocolName); header.print(cppName); header.print("Name ");
            } else {
                header.print("    static const "); header.print(_protocolName); header.print("AttributeName ");
            }
            header.print(cppName); header.println(";");

            header.println();
        }
        header.println();

        header.print("    ");
        header.print(_protocolName);
        header.print("AttributeName(const char *n, const AvpBuilder &m, const ImpBuilder &p, unsigned code, unsigned vendor = 0, bool mandatory = true, bool encrypt = true): AttributeName(n, m, p, code, vendor, mandatory, encrypt");
        if (isBase) {
            header.println(", true), AttributeCodeMap(this) {}");
        } else {
            header.println(", false) {}");
        }
        header.println("};");
        header.println();
        source.println();

        // Generate group attribute names definitions
        for (Map.Entry<String, AGroupedDefinition> entry: analyzer.getGroupedAVPs().entrySet()) {
            AGroupedDefinition node = entry.getValue();
            String rfcName = node.getName().getText();
            String cppName = rfcName.replaceAll("-", "");
            ADerivedDefinition definition = analyzer.getDerivedAVPs().get(rfcName);
            AGroupedBody body = (AGroupedBody)node.getGroupedBody();

            generateGroupedAVPInfoDef(source, analyzer, cppName, true, body.getFixed().iterator());
            generateGroupedAVPInfoDef(source, analyzer, cppName, true, body.getRequired().iterator());
            generateGroupedAVPInfoDef(source, analyzer, cppName, false, body.getOptional().iterator());
            source.println();

            source.print(_protocolName); source.print(cppName); source.print("Name::");
            source.print(_protocolName); source.print(cppName);
            source.println("Name(const char *n, const AvpBuilder &ap, const ImpBuilder &ip, unsigned avp, unsigned vid, bool mand, bool enc, bool base)");
            source.print(": GroupedAttributeName(n, ap, ip, avp, vid, mand, enc, base)");
            if (isBase) {
                source.println(", AttributeCodeMap(this) {");
            } else {
                source.println(" {");
            }

            generateGroupedAVPMapSetup(source, analyzer, true, body.getFixed().iterator());
            generateGroupedAVPMapSetup(source, analyzer, true, body.getRequired().iterator());
            generateGroupedAVPMapSetup(source, analyzer, false, body.getOptional().iterator());
            source.println("}");
            source.println();
        }

        String vid = analyzer.getGrammar().getVendorId() != null ? analyzer.getGrammar().getVendorId().getText() : "0";
        for (ADerivedDefinition def: avps) {
            String rfcName = def.getName().getText();
            String cppName = rfcName.replaceAll("-", "");

            String mandatory = new AvpFlagSet((AAvpFlagRules)def.getAvpFlagRules()).getFlags()[AvpFlagSet.MANDATORY];
            String protect   = new AvpFlagSet((AAvpFlagRules)def.getAvpFlagRules()).getFlags()[AvpFlagSet.PROTECTED];
            source.println();
            source.print("diameter::AVP *"); source.print(_protocolName); source.print("AttributeName::");
            source.print(cppName); source.print("AvpBuilder::"); source.println("build(const diameter::AVPImpl *impl) const {");
            source.print("    return new "); printNamespaces(source, _namespaces[_namespaces.length-1]); source.print(cppName); source.println("(impl);");
            source.println("}");

            source.print("struct "); source.print(_protocolName); source.print("AttributeName::");
            source.print(cppName); source.print("AvpBuilder ");
            source.print(_protocolName); source.print("AttributeName::_");
            source.print(cppName); source.println("AvpBuilder;");

            source.print("const "); printAttributeType(source, analyzer, rfcName); source.print(' ');
            printAttributeName(source, analyzer, rfcName);
            source.print("(\""); source.print(rfcName); source.print("\", "); source.print(_protocolName);
            source.print("AttributeName::_"); source.print(cppName); source.print("AvpBuilder, ");
            source.print(OpenDiameterUtil.getCxxTypeName(def.getAvpType()));
            source.print("ImpBuilder, ");
            source.print(def.getAvpCode()); source.print(", ");
            source.print(def.getVendorId() != null ? def.getVendorId().getText() : vid); source.print(", ");
            source.print(mandatory != null && (mandatory.equals(AvpFlagSet.MUST) || mandatory.equals(AvpFlagSet.MAY))); source.print(", ");

            source.print(protect != null && protect.equals(AvpFlagSet.MUST)); 

            source.println(");");
            source.println();

        }

        // Generate AVP classes
        for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
            generateAvpClass(header, source, entry.getValue(), analyzer);
        }
        closeNamespaces(header, _namespaces[_namespaces.length - 1]);
        header.println();
        header.println("#endif//_" + _protocolName + "AVP_H_");
        header.close();

        closeNamespaces(source, _namespaces[_namespaces.length - 1]);
        source.close();
    }

    private void printIncludesForCopyMethods(PrintWriter source,SemanticAnalyzer analyzer,SemanticAnalyzer analyzer1) 
    {
        printCommonIncludesForTransformer(source);
        source.println("#include <diameter/Exceptions.h>");
        source.println("#include <diameter/s6a_r10/UpdateLocation.h>");
        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet()) {
            CommandPair pair = entry.getValue();
            String clsName = pair.name.replaceAll("-", "");

            String[] name = _namespaces[_namespaces.length - 1];

            source.print("#include <");
            for (int i = 0; i < _namespaces[_namespaces.length - 1].length; ++i) {
                source.print(_namespaces[_namespaces.length - 1][i]); source.print('/');
            }
            source.print(clsName); source.println(".h>");
        }
        for (Map.Entry<String, CommandPair> entry: analyzer1.getCommands().entrySet()) {
            CommandPair pair = entry.getValue();
            String clsName = pair.name.replaceAll("-", "");

            String[] name = _namespaces1[_namespaces1.length - 1];

            source.print("#include <");
            for (int i = 0; i < _namespaces1[_namespaces1.length - 1].length; ++i) {
                source.print(_namespaces1[_namespaces1.length - 1][i]); source.print('/');
            }
            source.print(clsName); source.println(".h>");
        }		

    }

    private void processCommandsForCopy(PrintWriter source,PrintWriter source1, SemanticAnalyzer analyzer,SemanticAnalyzer analyzer1, String TransformerclsName) throws IOException
    {		
        char ss = 'i';
        int a = (int)(ss);
        a = a + 1;
        ss = (char)(a);

        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet())
        {
            CommandPair pair = entry.getValue();
            String clsName = pair.name.replaceAll("-", "");
            if (pair.req != null) 
            {
                source.println("");
                //Generate Copy Method for transformer
                source.print("void " + TransformerclsName + "::");
                printCopyMethodForTransformer(source,clsName,_protocolName,_protocolName1,true);
                source.print("( ");
                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Request");source.print(" &fromMsg ,");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);				
                source.print(clsName);source.print("Request");source.println(" &toMsg )");
                source.println("{");
                ACommandBody body = (ACommandBody)pair.req.getCommandBody();
                generateCopyPrinting(source, clsName, 1, body.getFixed().iterator(),analyzer,analyzer1,_protocolName1,true);
                generateCopyPrinting(source, clsName, 1, body.getRequired().iterator(),analyzer,analyzer1,_protocolName1,true);
                generateCopyPrinting(source, clsName, 0, body.getOptional().iterator(),analyzer,analyzer1,_protocolName1,true);

                //Invoke the method that will fill the new AVP's
                source.print("    ");
                printFillMethodForTransformer(source,clsName,_protocolName,_protocolName1,true);
                source.println("(toMsg);");

                source.println("}"); 
                source.println("");

                //Generate blank methods to fill the new AVP's with configurable values.
                source1.print("void " + TransformerclsName + "::");
                printFillMethodForTransformer(source1,clsName,_protocolName,_protocolName1,true);
                source1.print("( ");
                printNamespaces(source1, _namespaces1[_namespaces1.length-1]);
                source1.print(clsName);source1.print("Request");source1.println(" &toMsg ) {");				 
                source1.println("}"); 
                source1.println("");

                //Generate blank methods for Configuration
                source1.print("void " + TransformerclsName + "::");
                printConfigureMethodForTransformer(source1,clsName,_protocolName,_protocolName1,true);				
                source1.println("(Json::Value* cfg ) {");
                source1.println("}"); 
                source1.println("");

            }
            if (pair.res != null)
            {
                source.println("");
                source.print("void " + TransformerclsName + "::");
                printCopyMethodForTransformer(source,clsName,_protocolName,_protocolName1,false);
                source.print("( ");
                printNamespaces(source, _namespaces[_namespaces.length-1]);source.print(clsName);source.print("Answer");source.print(" &fromMsg ,");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);source.print(clsName);source.print("Answer");source.println(" &toMsg )");
                source.println("{");
                ACommandBody body = (ACommandBody)pair.res.getCommandBody();
                generateCopyPrinting(source, clsName, 1, body.getFixed().iterator(),analyzer,analyzer1,_protocolName1,false);
                generateCopyPrinting(source, clsName, 1, body.getRequired().iterator(),analyzer,analyzer1,_protocolName1,false);
                generateCopyPrinting(source, clsName, 0, body.getOptional().iterator(),analyzer,analyzer1,_protocolName1,false);

                //Invoke the method that will fill the new AVP's
                source.print("    ");
                printFillMethodForTransformer(source,clsName,_protocolName,_protocolName1,false);
                source.println("(toMsg);");

                source.println("}"); 
                source.println("");

                //Generate blank methods to fill the new AVP's with configurable values.
                source1.print("void " + TransformerclsName + "::");
                printFillMethodForTransformer(source1,clsName,_protocolName,_protocolName1,false);
                source1.print("( ");
                printNamespaces(source1, _namespaces1[_namespaces1.length-1]);
                source1.print(clsName);source1.print("Answer");source1.println(" &toMsg ) {");
                source1.println("}"); 
                source1.println("");

                //Generate blank methods for Configuration
                source1.print("void " + TransformerclsName + "::");
                printConfigureMethodForTransformer(source1,clsName,_protocolName,_protocolName1,false);				
                source1.println("(Json::Value* cfg ) {");
                source1.println("}"); 
                source1.println("");
            }

        }
        for (Map.Entry<String, CommandPair> entry: analyzer1.getCommands().entrySet())
        {
            CommandPair pair = entry.getValue();
            String clsName = pair.name.replaceAll("-", "");

            if (pair.req != null) 
            {
                source.println("");
                source.print("void " + TransformerclsName + "::");
                printCopyMethodForTransformer(source,clsName,_protocolName1,_protocolName,true);
                source.print("( ");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);
                source.print(clsName);source.print("Request");source.print(" &fromMsg ,");
                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Request");source.println(" &toMsg )");
                source.println("{");
                ACommandBody body = (ACommandBody)pair.req.getCommandBody();
                generateCopyPrinting(source, clsName, 1, body.getFixed().iterator(),analyzer1,analyzer,_protocolName,true);
                generateCopyPrinting(source, clsName, 1, body.getRequired().iterator(),analyzer1,analyzer,_protocolName,true);
                generateCopyPrinting(source, clsName, 0, body.getOptional().iterator(),analyzer1,analyzer,_protocolName,true);

                //Invoke the method that will fill the new AVP's
                source.print("    ");
                printFillMethodForTransformer(source,clsName,_protocolName1,_protocolName,true);
                source.println("(toMsg);");

                source.println("}"); 
                source.println("");

                //Generate blank methods to fill the new AVP's with configurable values.
                source1.print("void " + TransformerclsName + "::");
                printFillMethodForTransformer(source1,clsName,_protocolName1,_protocolName,true);
                source1.print("( ");
                printNamespaces(source1, _namespaces[_namespaces.length-1]);
                source1.print(clsName);source1.print("Request");source1.println(" &toMsg ) {");
                source1.println("}"); 
                source1.println("");


                //Generate blank methods for Configuration
                source1.print("void " + TransformerclsName + "::");
                printConfigureMethodForTransformer(source1,clsName,_protocolName1,_protocolName,true);				
                source1.println("(Json::Value* cfg ) {");
                source1.println("}"); 
                source1.println("");

            }
            if (pair.res != null)
            {
                source.println("");
                source.print("void " + TransformerclsName + "::");
                printCopyMethodForTransformer(source,clsName,_protocolName1,_protocolName,false);
                source.print("( ");
                printNamespaces(source, _namespaces1[_namespaces1.length-1]);
                source.print(clsName);source.print("Answer");	source.print(" &fromMsg ,");
                printNamespaces(source, _namespaces[_namespaces.length-1]);
                source.print(clsName);source.print("Answer");source.println(" &toMsg )");
                source.println("{");
                ACommandBody body = (ACommandBody)pair.res.getCommandBody();
                generateCopyPrinting(source, clsName, 1, body.getFixed().iterator(),analyzer1,analyzer,_protocolName,false);
                generateCopyPrinting(source, clsName, 1, body.getRequired().iterator(),analyzer1,analyzer,_protocolName,false);
                generateCopyPrinting(source, clsName, 0, body.getOptional().iterator(),analyzer1,analyzer,_protocolName,false);

                //Invoke the method that will fill the new AVP's
                source.print("    ");
                printFillMethodForTransformer(source,clsName,_protocolName1,_protocolName,false);
                source.println("(toMsg);");

                source.println("}"); 
                source.println("");

                //Generate blank methods to fill the new AVP's with configurable values.
                source1.print("void " + TransformerclsName + "::");
                printFillMethodForTransformer(source1,clsName,_protocolName1,_protocolName,false);
                source1.print("( ");
                printNamespaces(source1, _namespaces[_namespaces.length-1]);
                source1.print(clsName);source1.print("Answer");source1.println(" &toMsg ) {");
                source1.println("}"); 
                source1.println("");

                //Generate blank methods for Configuration
                source1.print("void " + TransformerclsName + "::");
                printConfigureMethodForTransformer(source1,clsName,_protocolName1,_protocolName,false);				
                source1.println("(Json::Value* cfg ) {");
                source1.println("}"); 
                source1.println("");				
            }

        }

    }
    private void processCommands(SemanticAnalyzer analyzer) throws IOException {
        ///////////////////////////////////////////////////////////
        // Generate a "generic" command class for base protocols //
        ///////////////////////////////////////////////////////////

        if (analyzer.getGrammar().getBase() != null) {
            String clsName = _protocolName + "GenericCommand";
            File file = new File(_hdrDirectory, clsName + ".h");
            //System.err.println("Generating header file " + file.getCanonicalPath());
            PrintWriter header = new PrintWriter(new FileWriter(file));
            header.println("#ifndef _" + clsName + "_H_");
            header.println("#define _" + clsName + "_H_");
            printAvpIncludes(header, _namespaces);
            header.println("#include <diameter/Command.h>");
            openNamespaces(header, _namespaces[_namespaces.length - 1]);

            file = new File(_srcDirectory, clsName + ".cpp");
            //System.err.println("Generating source file " + file.getCanonicalPath());
            PrintWriter source = new PrintWriter(new FileWriter(file));
            source.println("#include <diameter/Exceptions.h>");
            source.print("#include <");
            for (int i = 0; i < _namespaces[_namespaces.length - 1].length; ++i) {
                source.print(_namespaces[_namespaces.length - 1][i]); source.print('/');
            }
            source.print(clsName); source.println(".h>");
            openNamespaces(source, _namespaces[_namespaces.length - 1]);

            generateGenericCommandClass(header, source, analyzer, clsName);

            closeNamespaces(header, _namespaces[_namespaces.length - 1]);
            header.println();
            header.println("#endif//_" + clsName + "_H_");
            header.close();

            closeNamespaces(source, _namespaces[_namespaces.length - 1]);
            source.close();
        }

        //////////////////////////////
        // Generate command classes //
        //////////////////////////////

        for (Map.Entry<String, CommandPair> entry: analyzer.getCommands().entrySet()) {
            CommandPair pair = entry.getValue();
            String clsName = pair.name.replaceAll("-", "");
            File file = new File(_hdrDirectory, clsName + ".h");
            //Fix for issue wherein the #ifdef for one header is same with other for same Message.
            String[] name = _namespaces[_namespaces.length - 1];

            PrintWriter header = new PrintWriter(new FileWriter(file));
            header.println("#ifndef _" + name[name.length -1 ].toUpperCase() +"_"+  clsName + "_H_");
            header.println("#define _" + name[name.length -1 ].toUpperCase() +"_"+  clsName + "_H_");
            printAvpIncludes(header, _namespaces);
            header.println("#include <diameter/Command.h>");
            openNamespaces(header, _namespaces[_namespaces.length - 1]);

            file = new File(_srcDirectory, clsName + ".cpp");
            PrintWriter source = new PrintWriter(new FileWriter(file));
            source.println("#include <diameter/Exceptions.h>");
            source.print("#include <");
            for (int i = 0; i < _namespaces[_namespaces.length - 1].length; ++i) {
                source.print(_namespaces[_namespaces.length - 1][i]); source.print('/');
            }
            source.print(clsName); source.println(".h>");
            openNamespaces(source, _namespaces[_namespaces.length - 1]);

            if (pair.req != null) generateCommandClass(header, source, analyzer, true, clsName, pair.code, pair.req);
            if (pair.res != null) generateCommandClass(header, source, analyzer, false, clsName, pair.code, pair.res);

            // Generate command attributes

            header.println();
            header.print("class "); header.print(clsName); header.println("Attribute {");
            header.println("public:");
            if (pair.req != null) {
                String cmdName = pair.req.getName().getText().replaceAll("-", "");
                header.print("    const static CommandAttribute "); header.print(cmdName); header.println(';');
            }
            if (pair.res != null) {
                String cmdName = pair.res.getName().getText().replaceAll("-", "");
                header.print("    const static CommandAttribute "); header.print(cmdName); header.println(';');
            }
            header.println("};");

            if (pair.req != null) {
                source.println();
                String cmdName = pair.req.getName().getText().replaceAll("-", "");
                source.print("const CommandAttribute "); source.print(clsName); source.print("Attribute::");
                source.print(cmdName); source.print('('); 
                source.print((clsName.startsWith("Accounting") && (_protocolName.compareTo("Base") == 0))?"3":analyzer.getGrammar().getId());
                source.print(", "); source.print(pair.code);
                source.println(',');
                ACommandBody body = (ACommandBody)pair.req.getCommandBody();
                generateCommandAVPInfo(source, analyzer, true, body.getFixed().iterator());
                generateCommandAVPInfo(source, analyzer, true, body.getRequired().iterator());
                generateCommandAVPInfo(source, analyzer, false, body.getOptional().iterator());
                source.println("    NULL");
                source.println(");");
            }
            if (pair.res != null) {
                source.println();
                String cmdName = pair.res.getName().getText().replaceAll("-", "");
                source.print("const CommandAttribute "); source.print(clsName); source.print("Attribute::");
                source.print(cmdName); source.print('('); 
                source.print((clsName.startsWith("Accounting") && (_protocolName.compareTo("Base") == 0))?"3":analyzer.getGrammar().getId());

                //source.print(analyzer.getGrammar().getId());
                source.print(", "); source.print(pair.code);
                source.println(',');
                ACommandBody body = (ACommandBody)pair.res.getCommandBody();
                if(cmdName.endsWith("PROXYABLEERROR"))
                {
                    generateCommandAVPInfo(source, analyzer, false, body.getFixed().iterator());
                }
                else
                {
                    generateCommandAVPInfo(source, analyzer, true, body.getFixed().iterator());
                }
                generateCommandAVPInfo(source, analyzer, true, body.getRequired().iterator());
                generateCommandAVPInfo(source, analyzer, false, body.getOptional().iterator());
                source.println("    NULL");
                source.println(");");
            }

            // generate tester

            file = new File(_tstDirectory, clsName + "Test.cpp");
            PrintWriter tester = new PrintWriter(new FileWriter(file));
            tester.println("#include <diameter/Exceptions.h>");
            tester.print("#include <");
            for (int i = 0; i < _namespaces[_namespaces.length - 1].length; ++i) {
                tester.print(_namespaces[_namespaces.length - 1][i]); tester.print('/');
            }
            tester.print(clsName); tester.println(".h>");
            if (pair.req != null) generateCommandComposer(tester, analyzer, pair.req);
            if (pair.res != null) generateCommandComposer(tester, analyzer, pair.res);

            closeNamespaces(header, _namespaces[_namespaces.length - 1]);
            header.println();
            header.println("#endif//_" + clsName + "_H_");
            header.close();

            closeNamespaces(source, _namespaces[_namespaces.length - 1]);
            source.close();

            tester.close();
        }
    }

    private void generateAvpDeclarations(PrintWriter header, ADerivedDefinition node) {
        header.print("class "); header.print(node.getName().getText().replaceAll("-", "")); header.println(";");
    }

    private void generateAvpClass(PrintWriter header, PrintWriter source, ADerivedDefinition node, SemanticAnalyzer analyzer) {
        String avpName = node.getName().getText();
        String clsName = avpName.replaceAll("-", "");

        //System.err.println("Generating class " + clsName);
        header.println();
        DocumentWriter.generateForClass(header, node);
        if (node.getAvpType() instanceof AGroupedAvpType) {
            header.print("class "); header.print(clsName); header.println(": public diameter::GroupedAVP {");
            header.println("public:");
            // the constructors
            DocumentWriter.generateForGroupedAVPConstructor(header, clsName);
            header.print("    "); header.print(clsName); header.println("()");
            header.print("    : GroupedAVP(");
            printAttributeName(header, analyzer, avpName);
            header.println(") {}");
            header.println();
            header.print("    "); header.print(clsName); header.println("(const AVPImpl *entry)");
            header.print("    : GroupedAVP(");
            printAttributeName(header, analyzer, avpName); header.print(", entry");
            header.println(") {}");
            // the accessors
            generateGroupedAVPAccessors(header, source, analyzer, avpName);
            // the print function
            header.println();
            /*
             * Added for RuleEngine
             */
            header.println("public:");
            header.println("    virtual std::stringstream &formatforRE(std::stringstream &) const;");
            header.println("    virtual std::stringstream &formatforRE(std::stringstream &out,const char *header) const ;");
            header.println();
            //End of Code for RuleEngine

            header.println("protected:");
            header.println("    virtual std::ostream &print(std::ostream &) const;");
            header.println("    AVP* createCopy() const;");
            generateGroupedPrinter(header, source, clsName, analyzer.getGroupedAVPs().get(avpName));
        } else {
            String valueType;
            header.print("class "); header.print(clsName); header.print(": public diameter::"); printDerivedClassName(header, node.getAvpType());
            header.println(" {");
            header.print("    typedef "); printDerivedClassName(header, node.getAvpType()); header.println(" Super;");
            header.println();
            header.println("public:");
            if (node.getAvpType() instanceof AEnumeratedAvpType) {
                header.print("    enum Value ");
                Iterator<PEnumerator> it = analyzer.getEnumeratedAVPs().get(avpName).getEnumerator().iterator();
                char eol = '{';
                while (it.hasNext()) {
                    header.println(eol);
                    AEnumerator enumerator = (AEnumerator)it.next();
                    header.print("        ");
                    header.print(enumerator.getName().getText());
                    header.print(" = ");
                    header.print(enumerator.getValue().getText());
                    eol = ',';
                }
                header.println();
                header.println("    };");
                header.println();
                valueType = "Value";
            } else {
                valueType = OpenDiameterUtil.getCxxTypeName(node.getAvpType());
            }
            DocumentWriter.generateForDerivedAVPConstructor(header, clsName, "value");
            header.print("    explicit "); header.print(clsName); header.print("(const "); header.print(valueType); header.println(" &value)");
            header.print("    : Super("); printAttributeName(header, analyzer, avpName);
            if (valueType.equals("Value")) {
                header.print(", static_cast<const ");
                header.print(OpenDiameterUtil.getCxxTypeName(node.getAvpType()));
                header.println(" &>(value)) {}");
            } else {
                header.println(", value) {}");
            }
            header.println();
            header.print("    explicit "); header.print(clsName); header.println("(const AVPImpl *entry)");
            header.print("    : Super("); printAttributeName(header, analyzer, avpName); header.println(", entry) {}");
        }

        header.println("};");
        header.println();
    }

    private void generateGroupedAVPAccessors(PrintWriter h, PrintWriter s, SemanticAnalyzer analyzer, String avpName) {
        AGroupedDefinition node = analyzer.getGroupedAVPs().get(avpName);
        AGroupedBody body = (AGroupedBody)node.getGroupedBody();
        generateAVPAccessors(h, s, analyzer, avpName, 1, body.getFixed().iterator());
        generateAVPAccessors(h, s, analyzer, avpName, 1, body.getRequired().iterator());
        generateAVPAccessors(h, s, analyzer, avpName, 0, body.getOptional().iterator());
    }

    private void generateGroupedPrinter(PrintWriter header, PrintWriter source, String clsName, AGroupedDefinition node) {
        source.println();
        source.print("AVP* ");
        source.print(clsName);
        source.println("::createCopy() const {");
        source.println("  if(_inbound.validate() == false)");
        source.println("  {");
        source.println("    throw CodecException(__FILE__, __LINE__,\"Mandatory AVP Missing\");");
        source.println("  }");
        source.print("  return new ");
        source.print(clsName);
        source.println("(*this);");
        source.println("}");

        source.println();
        source.print  ("std::ostream &"); source.print(clsName); source.println("::print(std::ostream &out) const {");
        source.println("    printHeader(out); out << \" {\" << std::endl;");
        AGroupedBody body = (AGroupedBody)node.getGroupedBody();
        generateAVPPrinting(source, clsName, 1, body.getFixed().iterator());
        generateAVPPrinting(source, clsName, 1, body.getRequired().iterator());
        generateAVPPrinting(source, clsName, 0, body.getOptional().iterator());
        source.println("    return out << '}';");
        source.println("}");

        /*
         * Added for RuleEngine
         */
        source.println("std::stringstream &"); source.print(clsName); 
        source.println("::formatforRE(std::stringstream &out) const {");
        source.println("	const char* header = getHeaderforRE();");
        generateAVPPrintingForRuleEngine(source, clsName, 1,body.getFixed().iterator(),true);
        generateAVPPrintingForRuleEngine(source, clsName, 1, body.getRequired().iterator(),true);
        generateAVPPrintingForRuleEngine(source, clsName, 0, body.getOptional().iterator(),true);
        source.println("    return out;");
        source.println("}");

        source.println("std::stringstream &"); source.print(clsName); 
        source.println("::formatforRE(std::stringstream &out,const char *parent) const {");
        source.println("	const char* parent_temp = getHeaderforRE();");
        source.println("	string h_temp(parent);");
        source.println("	h_temp.append(\".\");");
        source.println("	h_temp+=parent_temp;");
        source.println("	const char* header = h_temp.c_str();");
        generateAVPPrintingForRuleEngine(source, clsName, 1,body.getFixed().iterator(),true);
        generateAVPPrintingForRuleEngine(source, clsName, 1, body.getRequired().iterator(),true);
        generateAVPPrintingForRuleEngine(source, clsName, 0, body.getOptional().iterator(),true);
        source.println("    return out;");
        source.println("}");

    }

    private void generateCommandAVPInfo(PrintWriter pw, SemanticAnalyzer analyzer, boolean mandatory, Iterator it) {
        while (it.hasNext()) {
            Object node = it.next();
            String name;
            if (node instanceof ANamedAvpRef) {
                name = ((ANamedAvpRef)node).getName().getText();
            } else { //AGeneralAvpRef
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                if (spec instanceof ANamedAvpSpec) {
                    name = ((ANamedAvpSpec)spec).getName().getText();
                } else { // AAnyAvpSpec
                    continue;
                }
            }
            SemanticAnalyzer avpAnalyzer = analyzer.getAnalyzerForAvp(name);
            boolean isBase = avpAnalyzer.getGrammar().getBase() != null;
            String code = avpAnalyzer.getDerivedAVPs().get(name).getAvpCode().getText();
            pw.print("    &"); printAttributeName(pw, analyzer, name); pw.print(", ");
            pw.print(mandatory); pw.print(", "); pw.print(isBase); pw.print(", "); pw.print(code);
            pw.println(',');
        }
    }

    private void generateGroupedAVPInfoDecl(PrintWriter h, SemanticAnalyzer analyzer, String clsName, boolean mandatory, Iterator it) {
        while (it.hasNext()) {
            Object node = it.next();
            String name;
            if (node instanceof ANamedAvpRef) {
                name = ((ANamedAvpRef)node).getName().getText();
            } else { //AGeneralAvpRef
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                if (spec instanceof ANamedAvpSpec) {
                    name = ((ANamedAvpSpec)spec).getName().getText();
                } else { // AAnyAvpSpec
                    continue;
                }
            }
            String cppName = name.replaceAll("-", "");
            ADerivedDefinition def = analyzer.getAnalyzerForAvp(name).getDerivedAVPs().get(name);
            boolean enc = ((AAvpFlagRules)def.getAvpFlagRules()).getEncryptable() instanceof AYesEncryptable;
            h.print("    static "); 
            //printAttributeType(h, analyzer, name); 
            if (def.getAvpType() instanceof AGroupedAvpType)
            {
                h.print("GroupedAttributeName");
            }
            else
            {
                h.print("AttributeName");
            }
            h.print(' '); h.print(cppName); h.println(';');
        }
    }

    //private void copyAVPswithinGroupedAVPs(PrintWriter h, SemanticAnalyzer analyzer, String clsName, boolean mandatory, Iterator it) {
    private void copyAVPswithinGroupedAVPs(PrintWriter source, SemanticAnalyzer analyzer, SemanticAnalyzer analyzer1,String clsName, int minOccurance, Iterator it,LinkedList linkedList,String protocolname,String toString,String fromString,char index) {
        Qualifier qualifier = new Qualifier();
        Qualifier qualifier1 = new Qualifier();
        int charToInt = (int)index;
        charToInt = charToInt + 1;
        char index1 = (char)charToInt;
        while (it.hasNext()) {
            Object node = it.next();
            String name;
            String name1;
            boolean found = false;
            if (node instanceof ANamedAvpRef) {
                qualifier = new Qualifier((AQualifier)((ANamedAvpRef)node).getQualifier(), minOccurance);
                name = ((ANamedAvpRef)node).getName().getText().replaceAll("-", "");
            } else {
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                qualifier = new Qualifier((AQualifier)((AGeneralAvpRef)node).getQualifier(), minOccurance);
                if (spec instanceof ANamedAvpSpec) {
                    name = ((ANamedAvpSpec)spec).getName().getText().replaceAll("-", "");
                } else {
                    continue;
                }
            }
            //System.out.print("Search for the AVP:");
            //System.out.println(name);
            Iterator  it1 = linkedList.iterator(); 
            while (it1.hasNext()) {
                Object node1 = it1.next();
                if (node1 instanceof ANamedAvpRef) {
                    qualifier1 = new Qualifier((AQualifier)((ANamedAvpRef)node1).getQualifier(), minOccurance);
                    name1 = ((ANamedAvpRef)node1).getName().getText().replaceAll("-", "");
                } else {
                    PAvpSpec spec1 = ((AGeneralAvpRef)node1).getAvpSpec();
                    qualifier1 = new Qualifier((AQualifier)((AGeneralAvpRef)node1).getQualifier(), minOccurance);
                    if (spec1 instanceof ANamedAvpSpec) {
                        name1 = ((ANamedAvpSpec)spec1).getName().getText().replaceAll("-", "");
                    } else {
                        continue;
                    }
                }
                if(name.equals(name1))
                {
                    found = true;
                    //System.out.print("Match Found  for AVP:");
                    //System.out.println(name);
                    break;
                }
            }
            if(found)
            {
                String cppName = name.replaceAll("-", "");
                boolean isGroupedAVP = false;
                for (Map.Entry<String, AGroupedDefinition> entry: analyzer.getGroupedAVPs().entrySet()) {
                    AGroupedDefinition Groupednode1 = entry.getValue();
                    String rfcName = Groupednode1.getName().getText();
                    String cppName1 = rfcName.replaceAll("-", "");

                    if(name.equals(cppName1))
                    {
                        isGroupedAVP = true;
                    }
                }
                if(isGroupedAVP == false)
                {
                    boolean BaseAVP = true;
                    for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
                        ADerivedDefinition node1 = entry.getValue();
                        String rfcName = node1.getName().getText();
                        String avpName = rfcName.replaceAll("-", "");
                        if(avpName.equals(name))
                        {
                            BaseAVP = false;
                            break;
                        }
                    } 
                    if ((qualifier.getMax() != qualifier1.getMax()) || (qualifier.getMin() != qualifier1.getMin()))
                    {
                        // System.out.print("Number of Instances does not Matches in both the release for AVP:");
                        //System.out.println(name);
                        continue;
                    }
                    if ((qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) &&
                            (qualifier1.getMax() > 1 || qualifier1.getMax() == Qualifier.INFINITY))
                    {
                        source.println("");
                        if(BaseAVP)
                        {
                            //source.print("    for (int i = 0; i < ");source.print(fromString);source.print(".count"); source.print(name); source.println("(); ++i) ");
                            source.print("    for (int ");source.print(index1);source.print(" = 0;");source.print(index1);source.print(" < ");
                            source.print(fromString);source.print(".count"); source.print(name); source.print("(); ++");source.print(index1);source.println(") ");
                            source.println("    {");
                            source.print("    ");source.print(toString);source.print(".add"); source.print(name);source.print("(");
                            source.print(fromString);source.print(".get");source.print(name);source.print("(");source.print(index1);source.println("));");
                            source.println("    }");
                        }
                        else
                        {
                            //source.print("    for (int i = 0; i < fromMsg.count"); source.print(name); source.println("(); ++i) ");
                            //source.print("    for (int i = 0; i < ");source.print(fromString);source.print(".count"); source.print(name); source.println("(); ++i) ");
                            source.print("    for (int ");source.print(index1);source.print(" = 0;");source.print(index1);source.print(" < ");
                            source.print(fromString);source.print(".count"); source.print(name); source.print("(); ++");source.print(index1);source.println(") ");
                            source.println("    {");
                            source.print("    ");source.print(toString);source.print(".add"); source.print(name); source.print("((const diameter::");source.print(protocolname);
                            source.print("::");source.print(name); source.print("&)");source.print("(");source.print(fromString);source.print(".get");
                            source.print(name);source.print("(");source.print(index1);source.println(")));");
                            source.println("    }");
                        }
                        source.println("");
                    }
                    else if(qualifier.getMin() < 1 && qualifier1.getMin() < 1)
                    {
                        source.println("");
                        if(BaseAVP)
                        {
                            //source.print("    if (fromMsg.contains"); source.print(name); source.println("()) {");
                            source.print("    if(");source.print(fromString);source.print(".contains"); source.print(name); source.println("()) {");
                            source.print("       ");source.print(toString);source.print(".set"); source.print(name);
                            source.print("(");source.print(fromString);source.print(".get");source.print(name);source.println("());");
                            source.println("    }");
                        }
                        else
                        {
                            source.print("    if(");source.print(fromString);source.print(".contains"); source.print(name); source.println("()) {");
                            source.print("       ");source.print(toString);source.print(".set");source.print(name);source.print("((const diameter::");source.print(protocolname);
                            source.print("::");source.print(name); source.print("&)"); source.print("(");source.print(fromString);source.print(".get");
                            source.print(name);source.println("()));");
                            source.println("    }");
                        }
                        source.println("");
                    }
                    else
                    {
                        source.println("");
                        if(BaseAVP)
                        {
                            source.print("    ");source.print(toString);source.print(".set"); source.print(name);
                            source.print("(");source.print(fromString);source.print(".get");source.print(name);source.println("());");
                        }
                        else 
                        {
                            source.print("    ");source.print(toString);source.print(".set");source.print(name);source.print("((const diameter::");source.print(protocolname);
                            source.print("::");source.print(name); source.print("&)");
                            source.print("(");source.print(fromString);source.print(".get");source.print(name);source.println("()));");
                        }
                        source.println("");
                    }


                }
                else
                {
                    source.println("");
                    AGroupedDefinition Groupednode1 = new AGroupedDefinition();
                    AGroupedDefinition Groupednode2 = new AGroupedDefinition();
                    for (Map.Entry<String, AGroupedDefinition> entry: analyzer.getGroupedAVPs().entrySet()) {
                        Groupednode1 = entry.getValue();
                        String rfcName = Groupednode1.getName().getText().replaceAll("-", "");
                        if(rfcName.equals(name))
                        {
                            break;
                        }
                    }
                    for (Map.Entry<String, AGroupedDefinition> entry: analyzer1.getGroupedAVPs().entrySet()) {
                        Groupednode2 = entry.getValue();
                        String rfcName = Groupednode2.getName().getText().replaceAll("-", "");
                        if(rfcName.equals(name))
                        {
                            break; 
                        }
                    }
                    AGroupedBody body1 = (AGroupedBody)Groupednode1.getGroupedBody();
                    AGroupedBody body2 = (AGroupedBody)Groupednode2.getGroupedBody();
                    if ((qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) &&
                            (qualifier1.getMax() > 1 || qualifier1.getMax() == Qualifier.INFINITY))
                    {
                        //source.print("    for (int i = 0; i < ");source.print(fromString);source.print(".count"); source.print(name); source.println("(); ++i) ");
                        source.print("    for (int ");source.print(index1);source.print("= 0;");source.print(index1);source.print(" < ");
                        source.print(fromString);source.print(".count"); source.print(name); source.print("(); ++");source.print(index1);source.println(") ");
                        source.println("    {");
                    }
                    else if(qualifier.getMin() < 1)
                    {
                        source.print("    if(");source.print(fromString);source.print(".contains"); source.print(name); source.println("())");
                        source.println("    {");
                    }
                    else
                    {
                    }
                    source.print("    diameter::");source.print(protocolname);source.print("::");source.print(name);
                    source.print(" "); source.print(name);source.println("_obj;");
                    String toString1 = name + "_obj";
                    String fromString1;
                    if ((qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) &&
                            (qualifier1.getMax() > 1 || qualifier1.getMax() == Qualifier.INFINITY))
                    {
                        //fromString1 = fromString + ".get" + name + "(i)";
                        fromString1 = fromString + ".get" + name + "(" + index1 + ")";
                    }
                    else
                    {
                        fromString1 = fromString + ".get" + name + "()";
                    }
                    copyAVPswithinGroupedAVPs(source, analyzer,analyzer1, name, 1, body1.getFixed().iterator(),body2.getFixed(),protocolname,toString1,fromString1,index1);
                    copyAVPswithinGroupedAVPs(source, analyzer,analyzer1, name, 1, body1.getRequired().iterator(),body2.getRequired(),protocolname,toString1,fromString1,index1);
                    copyAVPswithinGroupedAVPs(source, analyzer,analyzer1, name, 0, body1.getOptional().iterator(),body2.getOptional(),protocolname,toString1,fromString1,index1);
                    //source.print("    toMsg.add"); source.print(name); source.print("(const_cast<");source.print("diameter::");
                    if ((qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) &&
                            (qualifier1.getMax() > 1 || qualifier1.getMax() == Qualifier.INFINITY))
                    {
                        //source.print("    ");source.print(toString);source.print(".add"); source.print(name); source.print("((const diameter::");source.print(protocolname);
                        //source.print("::");source.print(name); source.print("&)");source.print("(");source.print(fromString);source.print(".get");
                        //source.print(name);source.println("(i)));");
                        source.print("    ");source.print(toString);source.print(".add");source.print(name); source.print("(const_cast<");source.print("diameter::");
                        source.print(protocolname);source.print("::");source.print(name);source.print("&>(");source.print(name);source.println("_obj));");
                        //source.println("    }");
                    }
                    else
                    {
                        //source.print("    ");source.print(toString);source.print(" .set");source.print(name);source.print("((const diameter::");source.print(protocolname);
                        //source.print("::");source.print(name); source.print("&)");
                        //source.print("(");source.print(fromString);source.print(".get");source.print(name);source.println("()));");
                        source.print("    ");source.print(toString);source.print(".set");source.print(name); source.print("(const_cast<");source.print("diameter::");
                        source.print(protocolname);source.print("::");source.print(name);source.print("&>(");source.print(name);source.println("_obj));");
                    }
                    if(((qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) &&
                                (qualifier1.getMax() > 1 || qualifier1.getMax() == Qualifier.INFINITY))||((qualifier.getMin() < 1)||(qualifier1.getMin() < 1)))
                    {
                        source.println("    }");
                    }
                    source.println("");
                }
            }
            //System.out.print("avpis:");
            //System.out.println(cppName);
        }
        /*ADerivedDefinition def = analyzer.getAnalyzerForAvp(name).getDerivedAVPs().get(name);
          boolean enc = ((AAvpFlagRules)def.getAvpFlagRules()).getEncryptable() instanceof AYesEncryptable;
          if (def.getAvpType() instanceof AGroupedAvpType)
          {
          System.out.print("GROUP AVP is:");
          System.out.println(cppName);
          }
          else
          {
          System.out.print("AVP is:");
          System.out.println(cppName);
          }
          */
        //System.out.println("***********************");
    }



    private void generateGroupedAVPInfoDef(PrintWriter s, SemanticAnalyzer analyzer, String clsName, boolean mandatory, Iterator it) {
        while (it.hasNext()) {
            Object node = it.next();
            String name;
            if (node instanceof ANamedAvpRef) {
                name = ((ANamedAvpRef)node).getName().getText();
            } else { //AGeneralAvpRef
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                if (spec instanceof ANamedAvpSpec) {
                    name = ((ANamedAvpSpec)spec).getName().getText();
                } else { // AAnyAvpSpec
                    continue;
                }
            }
            String cppName = name.replaceAll("-", "");
            ADerivedDefinition def = analyzer.getAnalyzerForAvp(name).getDerivedAVPs().get(name);
            boolean enc = ((AAvpFlagRules)def.getAvpFlagRules()).getEncryptable() instanceof AYesEncryptable;

            // printAttributeType(s, analyzer, name); 

            if (def.getAvpType() instanceof AGroupedAvpType)
            {
                s.print("GroupedAttributeName");
            }
            else
            {
                s.print("AttributeName");
            }

            s.print(' ');
            s.print(_protocolName); s.print(clsName); s.print("Name::"); s.print(cppName);
            s.print("(\""); s.print(name); s.print("\", ");
            printAttributeNamespace(s, analyzer, name);
            s.print('_'); s.print(cppName); s.print("AvpBuilder, ");
            s.print(OpenDiameterUtil.getCxxTypeName(def.getAvpType())); s.print("ImpBuilder, ");
            s.print(def.getAvpCode()); s.print(", ");
            String vid = analyzer.getGrammar().getVendorId() != null ? analyzer.getGrammar().getVendorId().getText() : "0";
            s.print(def.getVendorId() != null ? def.getVendorId().getText() : vid); s.print(", ");
            s.print(mandatory); s.print(", ");
            s.print(enc);
            if(_protocolName.compareTo("Base") == 0)
            {
                s.print(", true");
            }
            else
            {
                s.print(", false");
            }
            s.println(");");
        }
    }

    private void generateGroupedAVPMapSetup(PrintWriter pw, SemanticAnalyzer analyzer, boolean mandatory, Iterator it) {
        while (it.hasNext()) {
            Object node = it.next();
            String name;
            if (node instanceof ANamedAvpRef) {
                name = ((ANamedAvpRef)node).getName().getText();
            } else { //AGeneralAvpRef
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                if (spec instanceof ANamedAvpSpec) {
                    name = ((ANamedAvpSpec)spec).getName().getText();
                } else { // AAnyAvpSpec
                    continue;
                }
            }
            String cpp = name.replaceAll("-", "");
            if (mandatory) {
                pw.print("    GetMandAttMap()[");
            } else {
                pw.print("    GetOptAttMap()[");
            }
            pw.print(cpp); pw.print(".GetCode()] = &"); pw.print(cpp); pw.println(';');
            pw.print("    "); pw.print(cpp);
            pw.println(".SetIndex(GetMandAttMap().size() + GetOptAttMap().size());");
        }
    }

    private void generateCommandClass(PrintWriter h, PrintWriter s, SemanticAnalyzer analyzer, boolean request, String clsName, int code, ACommandDefinition node) {
        String rfcName = node.getName().getText();
        String cmdName = rfcName.replaceAll("-", "");
        ACommandHeader head = (ACommandHeader)node.getCommandHeader();
        String proxyable = head.getPxy() != null ? "true" : "false";
        h.println();
        DocumentWriter.generateForClass(h, node);
        h.print("class "); h.print(cmdName); h.println(": public diameter::Command {");
        h.println("public:");
        // the constructors
        DocumentWriter.generateForCommandConstructor(h, cmdName);
        h.print("    "); h.print(cmdName); 

        if(cmdName.endsWith("PROXYABLEERROR"))
        {
            h.println("( " + "bool error = false, bool retrans = false, int code = 0)");
        }
        else
        {
            h.println("(" + "bool error = false, bool retrans = false, bool proxy = " + proxyable + ")");
        }

        h.print("    : Command(");
        h.print(request); h.print(", "); 

        if(cmdName.endsWith("PROXYABLEERROR"))
        {
            h.print(proxyable); h.print(", error, retrans, ");
            h.print("code");
        }
        else
        {
            h.print("proxy, error, retrans, ");
            h.print(head.getCommandId().getText());
        }

        h.print(", "); 

        if(((ACommandHeader)node.getCommandHeader()).getApplicationId() == null)
        {
            h.print((cmdName.startsWith("Accounting")?"3":"0"));
        }
        else
        {
            h.print(_protocolId);
        }
        h.println(") {");
        h.println("        SetCmdAttribute(_desc);");
        h.println("    }");
        h.println();

        DocumentWriter.generateForCommandConstructor(h, cmdName, "buffer", "size");
        h.print("    "); h.print(cmdName); h.println("(const unsigned char *buffer, int size): Command(buffer, size, _desc) {");
        if (code > 0) h.println("        validate();");
        h.println("    }");
        h.println();

        DocumentWriter.generateForCommandConstructor(h, cmdName, "generic");
        h.print("    "); h.print(cmdName); h.println("(GenericCommand &generic): Command(generic.transfer(_desc)) {");
        if (code > 0) h.println("        validate();");
        h.println("    }");
        h.println();

        h.print("    "); h.print(cmdName); h.println("(const CommandImpl &impl): Command(impl, _desc) {");
        if (code > 0) h.println("        validate();");
        h.println("    }");
        s.println();
        s.print("const CommandAttribute *");
        s.print(cmdName); s.print("::_desc = &"); s.print(clsName); s.print("Attribute::"); s.print(cmdName);
        s.println(';');
        s.println();
        if (code > 0) {
            s.print("void "); s.print(cmdName); s.println("::validate() const {");
            s.print("    if (_inbound.getCommandCode() != "); s.print(head.getCommandId().getText());
            s.print(request ? " || !" : " || "); s.println("_inbound.isRequest()) {");
            s.println("        throw WrongCommandTypeException(__FILE__, __LINE__, _inbound.getCommandName());");
            s.println("    }");
            s.println("}");
        }
        if ((code != 257) && (code != 282) && (code != 280))
        {
            s.print("unsigned int ");
            s.print(cmdName);
            s.println("::getSessionIndex() {"); 
            s.println("    return Command::getSessionIndex();");
            s.println("}");
            s.print("void ");
            s.print(cmdName);
            s.println("::setSessionIndex(unsigned int index) {");
            s.println("     Command::setSessionIndex(index);");
            s.println("}");
        }

        if (code == 271)
        {
            s.print("bool ");
            s.print(cmdName);
            s.println("::IsStorageSpaceAvailable() {");
            s.println("    return Command::IsStorageSpaceAvailable();");
            s.println("}");
            s.print("void ");
            s.print(cmdName);
            s.println("::setStorageSpaceAvailable(bool index) {");
            s.println("     Command::setStorageSpaceAvailable(index);");
            s.println("}");

            s.print("bool ");
            s.print(cmdName);
            s.println("::IsLastRecordInStorage() {");
            s.println("    return Command::IsLastRecordInStorage();");
            s.println("}");
            s.print("void ");
            s.print(cmdName);
            s.println("::setLastRecordInStorage(bool index) {");
            s.println("     Command::setLastRecordInStorage(index);");
            s.println("}");

        }

        // the accessors
        generateCommandAVPAccessors(h, s, analyzer, rfcName, node);
        //proprietary changes--to facilitate setting session index
        if ((code != 257) && (code != 282) && (code != 280))
        {
            h.println();
            h.print("    void ");
            h.print("Copy");h.print(cmdName);h.print("Release8ToRelease10(");
            h.print(cmdName);h.println("& Release10,");h.print("           ");
            h.print(cmdName);h.println("& Release8);"); 
            s.println();
            s.print  ("void "); s.print(cmdName); s.print("::Copy"); s.print( cmdName); s.println("Release8ToRelease10(");
            s.print( cmdName);s.print("& Release10,");s.print( cmdName);s.println(" & Release8)");
            s.println("{");

            s.println("}");
            h.println();
            h.println("    /**");
            h.println("     * ITS-Diameter Specific:Refer DiaFrame::AllocateSessionIndex");
            h.println("     *");
            h.println("     * Returns sessionIndex");
            h.println("     */");
            h.print("    unsigned int getSessionIndex();");
            h.println();
            h.println("    /**");
            h.println("     * ITS-Diameter Specific:Refer DiaFrame::AllocateSessionIndex");
            h.println("     *");
            h.println("     * @ index : must be same as returned by");
            h.println("     * DiaFrame::AllocateSessionIndex");
            h.println("     */");
            h.print("    void setSessionIndex(unsigned int index);");
        }
        //proprietary changes--to facilitate setting session index

        if (code == 271)
        {

            // proprietary changes--to facilitate setting StorageSpaceAvailable   
            // flag for ACR
            h.println();
            h.println("    /**");
            h.println("     * ITS-Diameter Specific:For Base Accounting SM");
            h.println("     *");
            h.println("     * Returns StorageSpaceAvailable");
            h.println("     */");
            h.print("    bool IsStorageSpaceAvailable();");
            h.println();
            h.println("    /**");
            h.println("     * ITS-Diameter Specific:For Base Accounting SM");
            h.println("     *");
            h.println("     * @ flag : must be same as returned by");
            h.println("     * StorageSpaceAvailable");
            h.println("     */");
            h.print("    void setStorageSpaceAvailable(bool flag);");

            // proprietary changes--to facilitate setting StorageSpaceAvailable   
            // flag for ACR
            h.println();
            h.println("    /**");
            h.println("     * ITS-Diameter Specific:For Base Accounting SM");
            h.println("     *");
            h.println("     * Returns LastRecordInStorage");
            h.println("     */");
            h.print("    bool IsLastRecordInStorage();");
            h.println();
            h.println("    /**");
            h.println("     * ITS-Diameter Specific:For Base Accounting SM");
            h.println("     *");            
            h.println("     * @ flag : must be same as returned by");
            h.println("     * LastRecordInStorage");
            h.println("     */");
            h.print("    void setLastRecordInStorage(bool flag);");

        }

        h.println();

        /*
         * Generating Code for DRE RuleEngine.
         */
        h.println("    /**");
        h.println("     * This function formats the diameter message");
        h.println("     * and generates a string output which can be");
        h.println("     * consumed by CLIPS as facts and perform Rule Processing.");
        h.println("     */");
        h.println("    std::stringstream &formDiameterMessageForRuleEngine(std::stringstream & out) const;");
        h.println();
        generateCommandFormatterForRuleEngine(h,s,cmdName,analyzer,node);

        /*
         * End of Code for DRE RuleEngine
         */

        h.println("protected:");
        h.println("    virtual std::ostream &print(std::ostream &) const;");
        generateCommandPrinter(h, s, cmdName, node);
        h.println();
        h.println("private:");
        if (code > 0) {
            h.println("    void validate() const;");
        }
        h.println("    const static CommandAttribute *_desc;");
        h.println("};");
        h.println();
    }
    /*
     * Generating Code for DRE RuleEngine.
     */
    private void generateCommandFormatterForRuleEngine(PrintWriter header,
            PrintWriter source, String clsName, SemanticAnalyzer analyzer, ACommandDefinition node) {
        source.println();
        source.print  ("std::stringstream &"); source.print(clsName); source.println("::formDiameterMessageForRuleEngine(std::stringstream &out) const{");
        source.println("    printHeaderForRuleEngine(out);");
        ACommandBody body = (ACommandBody)node.getCommandBody();
        generateAVPPrintingForRuleEngine(source, clsName, 1, body.getFixed().iterator(),false);
        generateAVPPrintingForRuleEngine(source, clsName, 1, body.getRequired().iterator(),false);
        generateAVPPrintingForRuleEngine(source, clsName, 0, body.getOptional().iterator(),false);
        source.println("    return out;");
        source.println("}");

    }

    private void generateAVPPrintingForRuleEngine(PrintWriter source, String clsName, int minOccurance, Iterator it,boolean headerPresent) {
        //boolean hasExtra = false;
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
                    //hasExtra = true;
                    continue;
                }
            }
            if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
                source.print("    for (int i = 0; i < count"); source.print(name); source.println("(); ++i) {");
                if(headerPresent)
                {
                    source.print("        get"); source.print(name); source.println("(i).formatforRE(out,header);");
                }
                else
                {
                    source.print("        get"); source.print(name); source.println("(i).formatforRE(out);");
                }
                source.println("    }");
            } else if (qualifier.getMin() < 1) {
                source.print("    if (contains"); source.print(name); source.println("()) {");
                if(headerPresent)
                {
                    source.print("        get"); source.print(name); source.println("().formatforRE(out,header);");
                }
                else
                {
                    source.print("        get"); source.print(name); source.println("().formatforRE(out);");
                }
                source.println("    }");
            } else {
                if(headerPresent)
                {                
                    source.print("    get"); source.print(name); source.println("().formatforRE(out,header);");
                }
                else
                {
                    source.print("    get"); source.print(name); source.println("().formatforRE(out);");
                }
            }
        }
        /*TODO: Commenting this for now becoz custom AVp's are not supported 
         * as part of Rule engine in Phase-1b.
         * if (hasExtra) {
         source.println("    getContainer().printExtras(out);");
         }*/
    }

    /*
     * End of Code for DRE RuleEngine
     */


    private void generateGenericCommandClass(PrintWriter h, PrintWriter s, SemanticAnalyzer analyzer, String clsName) {
        h.println();
        h.println("/**");
        h.println(" * This class defines a <i>generic</i> Command interface that allows free access");
        h.println(" * to all possible AVP values defined in this base protocol.");
        h.println(" */");
        h.print  ("class "); h.print(clsName); h.println(": public diameter::GenericCommand {");
        h.println("public:");

        // the constructors
        DocumentWriter.generateForCommandConstructor(h, clsName, "buffer", "size");
        h.print("    "); h.print(clsName); h.println("(const unsigned char *buffer, int size): GenericCommand(buffer, size) {}");
        h.println();

        DocumentWriter.generateForCommandConstructor(h, clsName, "copy");
        h.print("    "); h.print(clsName); h.print("("); h.print(clsName); h.println(" &copy): GenericCommand(copy) {}");
        h.println();


        //New Constructor for DTF transformation
        h.print("    "); h.print(clsName); h.print("("); h.println("CommandImpl &cmdImpl): GenericCommand(cmdImpl) {}");
        h.println();

        DocumentWriter.generateForGetter(h, "DiaHeader", null);
        h.println("    const DiaHeader &getHeader() const {");
        h.println("        return const_cast<CommandImpl &>(getImpl()).getHeader();");
        h.println("    }");

        // the accessors
        for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
            generateGettersForGeneric(h, s, analyzer, clsName, new Qualifier(), entry.getValue().getName().getText());
        }

        h.println();
        h.println("    /**");  
        h.println("     * ITS-Diameter Specific:For IDS-Distributed Framework");            
        h.println("     *");
        h.println("     * @ clientId : must be set by IDS");
        h.println("     */");
        h.println("    void setClientId(unsigned int clientId)");
        h.println("    {");
        h.println("       unsigned int& _clientId = getClientId();");
        h.println("       _clientId = clientId;");
        h.println("    }");
        h.println("    /**");  
        h.println("     * ITS-Diameter Specific:For IDS-Distributed Framework");
        h.println("     *");
        h.println("     * Returns clientId");
        h.println("     */"); 
        h.println("    unsigned int& getClientId()");
        h.println("    {");
        h.println("      CommandImpl& impl = (CommandImpl&)_inbound;");
        h.println("      return impl.getClientId();");
        h.println("    }");
        h.println("protected:");
        h.println("    virtual std::ostream &print(std::ostream &) const;");

        //generateCommandPrinter(h, s, clsName, node);
        s.println();
        s.print  ("std::ostream &"); s.print(clsName); s.println("::print(std::ostream &out) const {");
        s.println("    printHeader(out); out << \" {\" << std::endl;");
        for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
            String name = entry.getValue().getName().getText().replaceAll("-", "");
            s.print("    for (int i = 0; i < count"); s.print(name); s.println("(); ++i) {");
            s.print("        out << \"    \" << get"); s.print(name); s.println("(i) << std::endl;");
            s.println("    }");
        }
        s.println("    return out << '}';");
        s.println("}");

        h.println("};");
        h.println();
    }

    private void generateCommandAVPAccessors(PrintWriter h, PrintWriter s, SemanticAnalyzer analyzer, String rfcName, ACommandDefinition node) {
        ACommandBody body = (ACommandBody)node.getCommandBody();
        generateAVPAccessors(h, s, analyzer, rfcName, 1, body.getFixed().iterator());
        generateAVPAccessors(h, s, analyzer, rfcName, 1, body.getRequired().iterator());
        generateAVPAccessors(h, s, analyzer, rfcName, 0, body.getOptional().iterator());
    }

    private void generateCommandPrinter(PrintWriter header, PrintWriter source, String clsName, ACommandDefinition node) {
        source.println();
        source.print  ("std::ostream &"); source.print(clsName); source.println("::print(std::ostream &out) const {");
        source.println("    printHeader(out); out << \" {\" << std::endl;");
        ACommandBody body = (ACommandBody)node.getCommandBody();
        generateAVPPrinting(source, clsName, 1, body.getFixed().iterator());
        generateAVPPrinting(source, clsName, 1, body.getRequired().iterator());
        generateAVPPrinting(source, clsName, 0, body.getOptional().iterator());
        source.println("    return out << '}';");
        source.println("}");
    }

    // Command tester

    public void generateCommandComposer(PrintWriter pw, SemanticAnalyzer analyzer, ACommandDefinition node) {
        String name = node.getName().getText().replaceAll("-", "");
        pw.println();
        pw.print("void test"); pw.print(name); pw.println("() {");
        pw.print("    "); printNamespaces(pw, _namespaces[_namespaces.length - 1]); pw.print(name);
        String var;

        ACommandHeader header = (ACommandHeader)node.getCommandHeader();
        if (header.getReq() != null) {
            var = "request";
        } else {
            var = "answer";
        }
        pw.print(' '); pw.print(var); pw.println(';');
        pw.println();
        ACommandBody body = (ACommandBody)node.getCommandBody();
        writeSetter(pw, analyzer, var, 1, body.getFixed().iterator());
        writeSetter(pw, analyzer, var, 1, body.getRequired().iterator());
        writeSetter(pw, analyzer, var, 0, body.getOptional().iterator());
        pw.println('}');
    }

    private void writeSetter(PrintWriter pw, SemanticAnalyzer analyzer, String var, int minOccurance, Iterator it) {
        boolean hasExtra = false;
        while (it.hasNext()) {
            Object node = it.next();
            Qualifier qualifier;
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
            pw.print("    "); pw.print(var);
            if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
                pw.print(".add");
            } else {
                pw.print(".set");
            }
            pw.print(name.replaceAll("-", "")); pw.print("("); printTypeReference(pw, analyzer, name); pw.println("(...));");
        }
        if (hasExtra) {
            pw.println("    // add more AVP as ANY values");
        }
    }

    // Shared by AVPs and Commands

    private void generateAVPAccessors(PrintWriter header, PrintWriter source, SemanticAnalyzer analyzer, String rfcName, int minOccurance, Iterator it) {
        while (it.hasNext()) {
            Object node = it.next();
            if (node instanceof ANamedAvpRef) {
                generateAccessors(header, source, analyzer, rfcName, new Qualifier((AQualifier)((ANamedAvpRef)node).getQualifier(), minOccurance), ((ANamedAvpRef)node).getName().getText());
            } else { //AGeneralAvpRef
                PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                if (spec instanceof ANamedAvpSpec) {
                    generateAccessors(header, source, analyzer, rfcName, new Qualifier((AQualifier)((AGeneralAvpRef)node).getQualifier(), minOccurance), ((ANamedAvpSpec)spec).getName().getText());
                } else { // AAnyAvpSpec
                    generateAccessors(header, source, analyzer, rfcName, new Qualifier((AQualifier)((AGeneralAvpRef)node).getQualifier(), minOccurance));
                }
            }
        }
    }

    private void generateAVPPrinting(PrintWriter source, String clsName, int minOccurance, Iterator it) {
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
                source.print("    for (int i = 0; i < count"); source.print(name); source.println("(); ++i) {");
                source.print("        out << \"    \" << get"); source.print(name); source.println("(i) << std::endl;");
                source.println("    }");
            } else if (qualifier.getMin() < 1) {
                source.print("    if (contains"); source.print(name); source.println("()) {");
                source.print("        out << \"    \" << get"); source.print(name); source.println("() << std::endl;");
                source.println("    }");
            } else {
                source.print("    out << \"    \" << get"); source.print(name); source.println("() << std::endl;");
            }
        }
        if (hasExtra) {
            source.println("    out << \"    \"; getContainer().printExtras(out); out << std::endl;");
        }
    }

    //Start of DTF
    private boolean isAVPPresentInOtherRelease(String clsName,SemanticAnalyzer analyzer1,boolean isRequest,String avpName)
    {
        for (Map.Entry<String, CommandPair> entry: analyzer1.getCommands().entrySet())
        {
            CommandPair pair = entry.getValue();
            String clsName1 = pair.name.replaceAll("-", "");
            String name = "nothing";
            if(clsName1.equals(clsName))
            {
                //ACommandBody body = (ACommandBody)pair.req.getCommandBody();
                ACommandBody body = new ACommandBody();
                if(isRequest)
                {
                    body = (ACommandBody)pair.req.getCommandBody();
                }
                else
                {
                    body = (ACommandBody)pair.res.getCommandBody();
                }
                Iterator it = body.getFixed().iterator();  
                while (it.hasNext()) 
                {
                    Object node = it.next();
                    if (node instanceof ANamedAvpRef)
                    {
                        name = ((ANamedAvpRef)node).getName().getText().replaceAll("-", "");
                    }
                    else
                    { 
                        PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                        if (spec instanceof ANamedAvpSpec) 
                        {
                            name = ((ANamedAvpSpec)spec).getName().getText().replaceAll("-", "");
                        } 
                        else 
                        { 
                            continue;
                        }
                    }
                    if(avpName.equals(name))
                    {
                        //System.out.print("AVP Present in both the releases:");
                        //System.out.println(name);

                        return true;
                    }
                }
                it = body.getRequired().iterator();
                while (it.hasNext()) 
                {
                    Object node = it.next();
                    if (node instanceof ANamedAvpRef)
                    {
                        name = ((ANamedAvpRef)node).getName().getText().replaceAll("-", "");
                    }
                    else
                    { 
                        PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                        if (spec instanceof ANamedAvpSpec) 
                        {
                            name = ((ANamedAvpSpec)spec).getName().getText().replaceAll("-", "");
                        } 
                        else 
                        { 
                            continue;
                        }
                    }
                    if(avpName.equals(name))
                    {
                        //System.out.print("AVP Present in both the releases:");
                        //System.out.println(name);
                        return true;
                    }
                }
                it = body.getOptional().iterator();
                while (it.hasNext()) 
                {
                    Object node = it.next();
                    if (node instanceof ANamedAvpRef)
                    {
                        name = ((ANamedAvpRef)node).getName().getText().replaceAll("-", "");
                    }
                    else
                    { 
                        PAvpSpec spec = ((AGeneralAvpRef)node).getAvpSpec();
                        if (spec instanceof ANamedAvpSpec) 
                        {
                            name = ((ANamedAvpSpec)spec).getName().getText().replaceAll("-", "");
                        } 
                        else 
                        { 
                            continue;
                        }
                    }
                    if(avpName.equals(name))
                    {
                        //System.out.print("AVP Present in both the releases:");
                        //System.out.println(name);
                        return true;
                    }
                }

            }
        }
        return false;
    }

    private void generateCopyPrinting(PrintWriter source, String clsName, int minOccurance, Iterator it,SemanticAnalyzer analyzer,SemanticAnalyzer analyzer1,String protocolname,boolean isRequest) {
        boolean hasExtra = false;
        Qualifier qualifier;
        String name;
        AGroupedDefinition Groupednode1 = new AGroupedDefinition();
        AGroupedDefinition Groupednode2 = new AGroupedDefinition();
        char index = 'i';

        while (it.hasNext()) {
            Object node = it.next();
            boolean BaseAVP = true;
            boolean otherrelease = false;
            boolean isGroupedAVP = false;
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
                for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
                    ADerivedDefinition node1 = entry.getValue();
                    String rfcName = node1.getName().getText();
                    String cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        BaseAVP = false;
                        break;
                    }
                }
                for (Map.Entry<String, AGroupedDefinition> entry: analyzer.getGroupedAVPs().entrySet()) {
                    Groupednode1 = entry.getValue();
                    String rfcName = Groupednode1.getName().getText();
                    String cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        BaseAVP = false;
                        isGroupedAVP = true;
                        break;
                    }
                }
                for (Map.Entry<String, ADerivedDefinition> entry: analyzer1.getDerivedAVPs().entrySet()) {
                    ADerivedDefinition node1 = entry.getValue();
                    String rfcName = node1.getName().getText();
                    String cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        //otherrelease = true;
                        break;
                    }
                }
                for (Map.Entry<String, AGroupedDefinition> entry: analyzer1.getGroupedAVPs().entrySet()) {
                    Groupednode2 = entry.getValue();
                    String rfcName = Groupednode2.getName().getText();
                    String cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        //otherrelease = true;
                        break;
                    }
                }
                otherrelease = isAVPPresentInOtherRelease(clsName,analyzer1,isRequest,name);
                if(BaseAVP)
                {
                    source.print("    for (int i = 0; i < fromMsg.count"); source.print(name); source.println("(); ++i) ");
                    source.println("    {");
                    source.print("    toMsg.add"); source.print(name);
                    source.print("(fromMsg.get");source.print(name);source.println("(i));");
                    source.println("    }");
                }
                else if(otherrelease)
                {
                    if(isGroupedAVP)
                    {
                        AGroupedBody body1 = (AGroupedBody)Groupednode1.getGroupedBody();
                        AGroupedBody body2 = (AGroupedBody)Groupednode2.getGroupedBody();
                        //System.out.print("Generating gropued avps");
                        //System.out.println(name);
                        source.print("    for (int i = 0; i < fromMsg.count"); source.print(name); source.println("(); ++i) ");
                        source.println("    {");
                        source.print("    diameter::");source.print(protocolname);source.print("::");source.print(name);
                        source.print(" "); source.print(name);source.println("_obj;");
                        String toString = name + "_obj";
                        String fromString = "fromMsg.get" + name + "(i)";
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 1, body1.getFixed().iterator(),body2.getFixed(),protocolname,toString,fromString,index);
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 1, body1.getRequired().iterator(),body2.getRequired(),protocolname,toString,fromString,index);
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 0, body1.getOptional().iterator(),body2.getOptional(),protocolname,toString,fromString,index);
                        source.print("    toMsg.add"); source.print(name); source.print("(const_cast<");source.print("diameter::");
                        source.print(protocolname);source.print("::");source.print(name);source.print("&>(");source.print(name);source.println("_obj));");
                        source.println("    }");
                    }
                    else
                    {
                        source.print("    for (int i = 0; i < fromMsg.count"); source.print(name); source.println("(); ++i) ");
                        source.println("    {");
                        source.print("    toMsg.add"); source.print(name); source.print("((const diameter::");source.print(protocolname);
                        source.print("::");source.print(name); source.print("&)");source.print("(fromMsg.get");source.print(name);source.println("(i)));");
                        source.println("    }");
                    }
                }
            } else if (qualifier.getMin() < 1) {
                for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
                    ADerivedDefinition node1 = entry.getValue();
                    String rfcName = node1.getName().getText();
                    String cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        BaseAVP = false;
                        break;
                    }
                }
                for (Map.Entry<String, AGroupedDefinition> entry: analyzer.getGroupedAVPs().entrySet()) {
                    Groupednode1 = entry.getValue();
                    String rfcName = Groupednode1.getName().getText();
                    String cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        BaseAVP = false;
                        isGroupedAVP = true;
                        break;
                    }
                }
                for (Map.Entry<String, ADerivedDefinition> entry: analyzer1.getDerivedAVPs().entrySet()) {
                    ADerivedDefinition node1 = entry.getValue();
                    String rfcName = node1.getName().getText();
                    String cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        //otherrelease = true;
                        break;
                    }
                }
                for (Map.Entry<String, AGroupedDefinition> entry: analyzer1.getGroupedAVPs().entrySet()) {
                    Groupednode2 = entry.getValue();
                    String rfcName = Groupednode2.getName().getText();
                    String cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        //otherrelease = true;
                        break;
                    }
                }
                otherrelease = isAVPPresentInOtherRelease(clsName,analyzer1,isRequest,name);
                if(BaseAVP)
                {
                    source.print("    if (fromMsg.contains"); source.print(name); source.println("()) {");
                    source.print("       toMsg.set"); source.print(name);
                    source.print("(fromMsg.get");source.print(name);source.println("());");
                    source.println("    }");
                }
                else if(otherrelease)
                {
                    if(isGroupedAVP)
                    {
                        AGroupedBody body1 = (AGroupedBody)Groupednode1.getGroupedBody();
                        AGroupedBody body2 = (AGroupedBody)Groupednode2.getGroupedBody();
                        //System.out.print("Generating gropued avps1:");
                        //System.out.println(name);
                        source.print("    if (fromMsg.contains"); source.print(name); source.println("())");
                        source.println("    {");
                        source.print("    diameter::");source.print(protocolname);source.print("::");
                        source.print(name);
                        source.print(" "); source.print(name);source.println("_obj;");
                        String toString = name + "_obj";
                        //String fromString = "fromMsg.get" + name + "(i)";
                        String fromString = "fromMsg.get" + name + "()";
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 1, body1.getFixed().iterator(),body2.getFixed(),protocolname,toString,fromString,index);
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 1, body1.getRequired().iterator(),body2.getRequired(),protocolname,toString,fromString,index);
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 0, body1.getOptional().iterator(),body2.getOptional(),protocolname,toString,fromString,index);
                        source.print("    toMsg.set"); source.print(name); source.print("(const_cast<");source.print("diameter::");
                        source.print(protocolname);source.print("::");source.print(name);source.print("&>(");source.print(name);source.println("_obj));");
                        source.println("    }");
                    }
                    else
                    {
                        source.print("    if (fromMsg.contains"); source.print(name); source.println("()) {");
                        source.print("       toMsg.set"); source.print(name);source.print("((const diameter::");source.print(protocolname);
                        source.print("::");source.print(name); source.print("&)"); source.print("(fromMsg.get");source.print(name);source.println("()));");
                        source.println("    }");
                    }
                }
            } else {
                String cppName ="shiva";
                for (Map.Entry<String, ADerivedDefinition> entry: analyzer.getDerivedAVPs().entrySet()) {
                    ADerivedDefinition node1 = entry.getValue();
                    String rfcName = node1.getName().getText();
                    cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        BaseAVP = false;
                        break;
                    }
                }
                for (Map.Entry<String, AGroupedDefinition> entry: analyzer.getGroupedAVPs().entrySet()) {
                    Groupednode1 = entry.getValue();
                    String rfcName = Groupednode1.getName().getText();
                    cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        BaseAVP = false;
                        isGroupedAVP = true;
                        break;
                    }
                }
                for (Map.Entry<String, ADerivedDefinition> entry: analyzer1.getDerivedAVPs().entrySet()) {
                    ADerivedDefinition node1 = entry.getValue();
                    String rfcName = node1.getName().getText();
                    cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        //otherrelease = true;
                        break;
                    }
                }
                for (Map.Entry<String, AGroupedDefinition> entry: analyzer1.getGroupedAVPs().entrySet()) {
                    Groupednode2 = entry.getValue();
                    String rfcName = Groupednode2.getName().getText();
                    cppName = rfcName.replaceAll("-", "");
                    if(cppName.equals(name))
                    {
                        //otherrelease = true;
                        break;
                    }
                }
                otherrelease = isAVPPresentInOtherRelease(clsName,analyzer1,isRequest,name);
                if(BaseAVP)
                { 
                    source.print("    toMsg.set"); source.print(name); 
                    source.print("(fromMsg.get");source.print(name);source.println("());");
                }
                else if(otherrelease)
                {
                    if(isGroupedAVP)
                    {
                        AGroupedBody body1 = (AGroupedBody)Groupednode1.getGroupedBody();
                        AGroupedBody body2 = (AGroupedBody)Groupednode2.getGroupedBody();
                        //System.out.print("Generating gropued avps2:");
                        //System.out.println(name);
                        source.print("    diameter::");source.print(protocolname);source.print("::");source.print(name);
                        source.print(" "); source.print(name);source.println("_obj;");
                        String toString = name + "_obj";
                        String fromString = "fromMsg.get" + name + "()";
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 1, body1.getFixed().iterator(),body2.getFixed(),protocolname,toString,fromString,index);
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 1, body1.getRequired().iterator(),body2.getRequired(),protocolname,toString,fromString,index);
                        copyAVPswithinGroupedAVPs(source, analyzer, analyzer1,name, 0, body1.getOptional().iterator(),body2.getOptional(),protocolname,toString,fromString,index);
                        source.print("    toMsg.set"); source.print(name); source.print("(const_cast<");source.print("diameter::");
                        source.print(protocolname);source.print("::");source.print(name);source.print("&>(");source.print(name);source.println("_obj));");
                    }
                    else
                    {
                        source.print("    toMsg.set"); source.print(name);source.print("((const diameter::");source.print(protocolname);
                        source.print("::");source.print(name); source.print("&)"); 
                        source.print("(fromMsg.get");source.print(name);source.println("()));");
                    }
                }

            }
        }
        if (hasExtra) {
            //source.println("    out << \"    \"; getContainer().printExtras(out); out << std::endl;");
        }
    } 
    //End of DTF

    // Generate getters for a base generic command
    private void generateGettersForGeneric(PrintWriter h, PrintWriter s, SemanticAnalyzer analyzer, String rfcName, Qualifier qualifier, String avpName) {
        String clsName = rfcName.replaceAll("-", "");
        String name = avpName.replaceAll("-", "");
        //System.err.println("generateAccessors for " + name + ", qual = " + qual + ", min = " + min);
        String setter = "set";
        boolean single = true;
        String hgetopt = "";
        String sgetopt = "";
        String getarg = "0";

        // Tester
        if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
            h.println();
            DocumentWriter.generateForCounter(h, name);
            h.print("    int count"); h.print(name); h.println("() const;");
            s.println();            s.print("int "); s.print(clsName); s.print("::count"); s.print(name); s.println("() const {");
            s.print("    return getContainer().count("); printMemberAttributeName(s, analyzer, rfcName, avpName); s.println(");");
            s.println("}");
            setter = "add";            single = false;
            hgetopt = "int index = 0";
            sgetopt = "int index";
            getarg = "index";
        } else if (qualifier.getMin() < 1) {
            h.println();
            DocumentWriter.generateForTester(h, name);
            h.print("    bool contains"); h.print(name); h.println("() const;");
            s.println();
            s.print("bool "); s.print(clsName); s.print("::contains"); s.print(name); s.println("() const {");
            s.print("    return getContainer().contains("); printMemberAttributeName(s, analyzer, rfcName, avpName); s.println(");");
            s.println("}");
        }

        // Getter
        h.println();
        DocumentWriter.generateForGetter(h, name, single ? null : "index");
        h.print  ("    const "); printTypeReference(h, analyzer, avpName); h.print(" *get"); h.print(name); h.print("("); h.print(hgetopt); h.println(") const;");
        s.println();
        s.print  ("const "); printTypeReference(s, analyzer, avpName); s.print(" *"); s.print(clsName); s.print("::get"); s.print(name); s.print("("); s.print(sgetopt); s.println(") const {");
        s.print  ("    return static_cast<const "); printTypeReference(s, analyzer, avpName); s.print(" *>(getContainer().getPtr("); printMemberAttributeName(s, analyzer, rfcName, avpName); s.print(", "); s.print(getarg); s.println("));");
        s.println("}");
    }

    // Generate accessors for a named AVP
    private void generateAccessors(PrintWriter h, PrintWriter s, SemanticAnalyzer analyzer, String rfcName, Qualifier qualifier, String avpName) {
        String clsName = rfcName.replaceAll("-", "");
        String name = avpName.replaceAll("-", "");
        //System.err.println("generateAccessors for " + name + ", qual = " + qual + ", min = " + min);
        String setter = "set";
        boolean single = true;
        String hgetopt = "";
        String sgetopt = "";
        String getarg = "0";

        // Tester
        if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
            h.println();
            DocumentWriter.generateForCounter(h, name);
            h.print("    int count"); h.print(name); h.println("() const;");
            s.println();
            s.print("int "); s.print(clsName); s.print("::count"); s.print(name); s.println("() const {");
            s.print("    return getContainer().count("); printMemberAttributeName(s, analyzer, rfcName, avpName); s.println(");");
            s.println("}");
            setter = "add";
            single = false;
            hgetopt = "int index = 0";
            sgetopt = "int index";
            getarg = "index";
        } else if (qualifier.getMin() < 1) {
            h.println();
            DocumentWriter.generateForTester(h, name);
            h.print("    bool contains"); h.print(name); h.println("() const;");
            s.println();
            s.print("bool "); s.print(clsName); s.print("::contains"); s.print(name); s.println("() const {");
            s.print("    return getContainer().contains("); printMemberAttributeName(s, analyzer, rfcName, avpName); s.println(");");
            s.println("}");
        }

        // Getter
        h.println();
        DocumentWriter.generateForGetter(h, name, single ? null : "index");
        h.print  ("    const "); printTypeReference(h, analyzer, avpName); h.print(" &get"); h.print(name); h.print("("); h.print(hgetopt); h.println(") const;");
        s.println();
        s.print  ("const "); printTypeReference(s, analyzer, avpName); s.print(" &"); s.print(clsName); s.print("::get"); s.print(name); s.print("("); s.print(sgetopt); s.println(") const {");

        s.print  ("    return static_cast<const "); printTypeReference(s, analyzer, avpName); s.print(" &>(getContainer().get("); printMemberAttributeName(s, analyzer, rfcName, avpName); s.print(", "); s.print(getarg); s.println("));");
        s.println("}");

        // Setter
        h.println();
        DocumentWriter.generateForSetter(h, name, "avp", single);
        h.print("    void "); h.print(setter); h.print(name); h.print("(const "); printTypeReference(h, analyzer, avpName); h.println(" &avp);");
        s.println();
        s.print("void "); s.print(clsName); s.print("::"); s.print(setter); s.print(name); s.print("(const "); printTypeReference(s, analyzer, avpName); s.println(" &avp) {");
        s.print("    getContainer().add(avp.name(), avp, "); s.print(single); s.println(");");
        s.println("}");
    }

    // generate accessors for "any" AVPs
    private void generateAccessors(PrintWriter h, PrintWriter s, SemanticAnalyzer analyzer, String rfcName, Qualifier qualifier) {
        //System.err.println("generateAccessors for ANY, qual = " + qual + ", min = " + min);
        String clsName = rfcName.replaceAll("-", "");
        String setter = "set";
        boolean single = true;
        String hgetopt = "";
        String sgetopt = "";
        String getarg = "0";

        // Tester
        if (qualifier.getMax() > 1 || qualifier.getMax() == Qualifier.INFINITY) {
            h.println();
            DocumentWriter.generateForAnyCounter(h, null);
            h.println("    int countExtra() const;");
            s.println();
            s.print  ("int "); s.print(clsName); s.println("::countExtra() const {");
            s.println("    return getContainer().countExtra(AttributeName::AVP);");
            s.println("}");
            h.println();
            DocumentWriter.generateForAnyCounter(h, "name");
            h.println("    int countExtra(const AttributeName &name) const;");
            s.println();
            s.print  ("int "); s.print(clsName); s.println("::countExtra(const AttributeName &name) const {");
            s.println("    return getContainer().countExtra(name);");
            s.println("}");
            setter = "add";
            single = false;
            hgetopt = ", int index = 0";
            sgetopt = ", int index";
            getarg = "index";
        } else if (qualifier.getMin() < 1) {
            h.println();
            DocumentWriter.generateForAnyTester(h, null);
            h.println("    bool containsExtra() const;");
            h.println();
            s.print  ("bool "); s.print(clsName); s.println("::containsExtra() const {");
            s.println("    return getContainer().contains(AttributeName::AVP);");
            s.println("}");
            h.println();
            DocumentWriter.generateForAnyTester(h, "name");
            h.println("    bool containsExtra(const AttributeName &) const;");
            s.println();
            s.print  ("bool "); s.print(clsName); s.println("::containsExtra(const AttributeName &name) const {");
            s.println("    return getContainer().containsExtra(name);");
            s.println("}");
        }

        // Getter
        h.println();
        DocumentWriter.generateForAnyGetter(h, "name", single ? null : getarg);
        h.print  ("    const AVP &getExtra(const AttributeName &name"); h.print(hgetopt); h.println(") const;");
        s.println();
        s.print  ("const AVP &"); s.print(clsName); s.print("::getExtra(const AttributeName &name"); s.print(sgetopt); s.println(") const {");
        s.print  ("    return getContainer().getExtra(name, "); s.print(getarg); s.println(");");
        s.println("}");

        // Setter
        h.println();
        DocumentWriter.generateForAnySetter(h, "avp", single);
        h.print  ("    void "); h.print(setter); h.println("Extra(const AVP &avp);");
        s.println();
        s.print  ("void "); s.print(clsName); s.print("::"); s.print(setter); s.println("Extra(const AVP &avp) {");
        s.print  ("    getContainer().add(AttributeName::AVP, avp, "); s.print(single); s.println(");");
        s.println("}");
    }



    public String getPluginName() {
        return pluginName;
    }



    public void setPluginName(String pluginName) {
        this.pluginName = pluginName;
    }
    }
