package diameter;

import com.intellinet.diameter.CodecException;
import diameter.VerificationException;
import java.lang.reflect.InvocationTargetException;
import java.util.*;


/**
 * A class used to invoke other classes' main methods.
 */
public class TestRunner {
    private static List<String> cantCode = new ArrayList<String>();
    private static List<String> cantVerify = new ArrayList<String>();

    /**
     * Invokes classes' main methods
     */
    public static void main(String[] args) {
        int total = 0;

        String[] dummy = new String[0];
        for (int i = 0; i < args.length; ++i) {
            try {
                ++total;
                report("TESTING", args[i], null);
                Class.forName(args[i]).getMethod("main", String[].class).invoke(null, (Object)dummy);
                report("+PASSED", args[i], "GOOD");
            } catch (InvocationTargetException x) {
                Throwable t = x.getCause();
                if (t instanceof CodecException) {
                    cantCode.add(args[i] + ": " + t.getMessage());
                    report("!FAILED", args[i], x.getMessage());
                    //break;
                } else if (t instanceof VerificationException) {
                    cantVerify.add(args[i]);
                    report("!FAILED", args[i], x.getMessage());
                    //break;
                }
            } catch (Throwable t) {
                report("!FAILED", args[i], t.getMessage());
                t.printStackTrace();
                //break;
            }
        }

        System.err.println("TEST SUMMARY: among " + total + " test case(s) ...");
        if (cantCode.isEmpty() && cantVerify.isEmpty()) {
            System.err.println("all passed");
        } else {
            if (!cantCode.isEmpty()) {
                System.err.println(cantCode.size() + " failed encoding/decoding:");
                for (int i = 0; i < cantCode.size(); ++i) {
                    System.err.println("\t" + cantCode.get(i));
                }
            }
            if (!cantVerify.isEmpty()) {
                System.err.println(cantVerify.size() + " failed verification:");
                for (int i = 0; i < cantVerify.size(); ++i) {
                    System.err.println("\t" + cantVerify.get(i)); 
                }
            }
        }
        System.err.println();
    }

    private static void report(String message, String testcase, String detail) {
        System.err.println();
        System.err.print('\t');
        System.err.print(message);
        System.err.print(" - ");
        System.err.print(testcase);
        if (detail != null) {
            System.err.print(": ");
            System.err.println(detail);
        } else {
            System.err.println();
        }
        System.err.println();
    }
}
