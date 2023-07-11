package com.intellinet.diameter.mag;

import java.io.*;
//import java.util.*;
import com.intellinet.diameter.mag.lexer.*;
import com.intellinet.diameter.mag.node.Start;
import com.intellinet.diameter.mag.parser.*;
import com.intellinet.diameter.mag.util.*;


public class Main {
	private static final String DICTIONARY = "--dictionary:";
	private static final String CPLUSPLUS  = "--c++:";
	private static final String JAVA       = "--java:";
	//Prem:Added for DTF
	private static final String DICTNAME       = "--dictname:";
	private static final String CONVERSION       = "--conversion:";
	private static final String PLUGINNAME       = "--pluginName:";
	private static final String DICTNAME1      = "--dict1:";
	private static final String DICTNAME2       = "--dict2:";

	private static void usage() {
		System.err.println("Usage: java -jar diamag.jar COMMANDS PROTOCOL1 PROTOCOL2 ...");
		System.err.println("  where COMMANDS can be any combination of");
		System.err.println("    --dictionary:FILE-NAME");
		System.err.println("    --c++:SOURCE-ROOT");
		System.err.println("    --java:SOURCE-ROOT");
		System.err.println("    --dictname:Dictionary-Name");
		System.exit(0);
	}

	public static void main(String[] args) {
		boolean showAST = true;
		String dictionary = null;
		String cplusplus = null;
		String java = null;
		String dictName = null;
		String dictName1 = null;
		String dictName2 = null;
		String pluginName = null;
		System.out.println("ENTERING");
		if (args.length < 1) {
			usage();
		}

		int index = 0;
		int index1 = 0;
		while (args[index].startsWith("-")) {
			//System.out.println("Index" + index);
			if (args[index].startsWith(DICTIONARY)) {
				dictionary = args[index].substring(DICTIONARY.length());
				if (dictionary.length() == 0) {
					System.err.println("No dictionary name provided");
				} else {
					showAST = false;
					System.out.println("No Dictionary");
				}
			} else if (args[index].startsWith(CPLUSPLUS)) {
				cplusplus = args[index].substring(CPLUSPLUS.length());
				if (cplusplus.length() == 0) {
					System.err.println("No C++ directory provided");
				} else {
					//System.out.println("Found cpluscplus");
					//System.out.println(cplusplus);
					showAST = false;
				}
			} else if (args[index].startsWith(CONVERSION)) {
				cplusplus = args[index].substring(CONVERSION.length());
				if (cplusplus.length() == 0) {
					System.err.println("No Conversion directory provided");
				} else {
					//System.out.println("Found Conversion");
					//System.out.println(cplusplus);
					showAST = false;
				}
			}else if (args[index].startsWith(JAVA)) {
				java = args[index].substring(JAVA.length());
				if (java.length() == 0) {
					System.err.println("No Java directory provided");
				} else {
					showAST = false;
					//System.out.println("No Java");
				}  
			} else if (args[index].startsWith(DICTNAME)) {	//Added for DTF
				dictName = args[index].substring(DICTNAME.length());
				if (dictName.length() == 0) {
					System.err.println("No Dictionary Name provided");
				} else {
					showAST = false;
				}
			} else if (args[index].startsWith(DICTNAME1)) {	//Added for DTF
				dictName1 = args[index].substring(DICTNAME1.length());
				if (dictName1.length() == 0) {
					System.err.println("No Dictionary1 Name provided");
				} else {
					showAST = false;
				}
			} else if (args[index].startsWith(DICTNAME2)) {	//Added for DTF
				dictName2 = args[index].substring(DICTNAME2.length());
				if (dictName2.length() == 0) {
					System.err.println("No Dictionary2 Name provided");
				} else {
					showAST = false;
				}
			} else if (args[index].startsWith(PLUGINNAME)) {	//Added for DTF
				pluginName = args[index].substring(PLUGINNAME.length());
				if (pluginName.length() == 0) {
					System.err.println("No Plugin Name provided");
				} else {
					showAST = false;
				}
			} 
			else {
				System.err.println("Unknown command " + args[index]);
			}
			++index;
			if(index >= args.length)
			{
				break;
			}
		}
		
		if(cplusplus == null)
		{
			if (index >= args.length) {
				usage();
			}
		}

		//List<SemanticAnalyzer> grammars = new ArrayList<SemanticAnalyzer>();

		try {
			//start_time = System.currentTimeMillis();
			//private String DTFMethodDirectory = "DTFMethods";  
			//File file = new File(cplusplus + "src/diameter/DTFMethods","DTFCopyMethods.cpp");
			//System.out.println("FILE CREATED");
			ODDGenerator dictionaryGen = (dictionary != null) ? new ODDGenerator(dictionary) : null;
			CxxGenerator cplusplusGen = (cplusplus != null) ? new CxxGenerator(cplusplus) : null;
			JavaGenerator javaGen = (java != null) ? new JavaGenerator(java) : null;
			SemanticAnalyzer analyzer = null;
			
			//Added for DTF
			if(dictName != null)
			{
				cplusplusGen.set_dictName(dictName);
			}
			
			if(pluginName != null)
			{
				cplusplusGen.setPluginName(pluginName);
			}
			
			SemanticAnalyzer analyzer1 = null;
			/*System.out.print("Argument length:");
			System.out.println(args.length);
			System.out.print("INDEX length:");
			System.out.println(index);
			System.out.print("INDEX1 length:");
			System.out.println(index1);*/
			if((dictName1 != null) || (dictName1 != null))
			{
				Lexer lexer = new Lexer(new PushbackReader(new BufferedReader(new FileReader(dictName1)), 1024));
				Lexer lexer1 = new Lexer(new PushbackReader(new BufferedReader(new FileReader(dictName2)), 1024));
				Parser parser = new Parser(lexer);
				Parser parser1 = new Parser(lexer1);
				Start ast = parser.parse();
				Start ast1 = parser1.parse();

				analyzer = new SemanticAnalyzer(analyzer);
				analyzer1 = new SemanticAnalyzer(analyzer1);
				ast.apply(analyzer);
				ast1.apply(analyzer1);
				cplusplusGen.process(analyzer,analyzer1);

			}
			//End of Addition for DTF
			else
			{
				for (int i = index; i < args.length; ++ i) {
					// create lexer
					/*System.out.print("args:");
					System.out.println(args[i]);*/ 
					Lexer lexer = new Lexer(new PushbackReader(new BufferedReader(new FileReader(args[i])), 1024));

					// parser program
					Parser parser = new Parser(lexer);

					Start ast = parser.parse();

					// check program semantics
					//ast.apply(new SemanticAnalyser());

					// generate class file
					//ast.apply(new ClassGenerator());
					//System.out.println(ast);
					analyzer = new SemanticAnalyzer(analyzer);
					ast.apply(analyzer);
					if (analyzer.isSatisfied()) {
						if (dictionaryGen != null) {
							dictionaryGen.generate(analyzer);
						}
						if (cplusplusGen != null) {
							cplusplusGen.process(analyzer);
						}
						if (javaGen != null) {
							javaGen.process(analyzer);
						}
						if (showAST) {
							ast.apply(new ASTDisplay());
						}
					}
					//grammars.add(analyzer);
				}
			}
			if (dictionaryGen != null) dictionaryGen.close();
		} catch (Exception e) {
			e.printStackTrace(System.out);
		}
	}
}
