package com.intellinet.diameter.mag.util;

import java.util.*;
import com.intellinet.diameter.mag.node.*;


public class AvpFlagSet {
    public static int MANDATORY = 0;
    public static int PROTECTED = 1;
    public static int VENDOR    = 2;

    public AvpFlagSet(AAvpFlagRules node) {
        setFlags(node.getMust(), MUST);
        setFlags(node.getMay(), MAY);
        setFlags(node.getShouldnt(), SHDNT);
        setFlags(node.getMustnt(), MUSNT);
    }

    public String[] getFlags() {
        return _flags;
    }

    public boolean isValid() {
        return _valid;
    }

    private void setFlags(LinkedList flags, String group) {
        Iterator it = flags.iterator();
        while (it.hasNext()) {
            PAvpFlag flag = (PAvpFlag)it.next();
            if (flag instanceof AMandatoryAvpFlag) {
                set(MANDATORY, group);
            } else if (flag instanceof APrivateAvpFlag) {
                set(PROTECTED, group);
            } else {
                set(VENDOR, group);
            }
        }
    }

    private void set(int type, String group) {
        if (_flags[type] == null) {
            _flags[type] = group;
        } else {
            _valid = false;
        }
    }

    public static final String MUST  = "must";
    public static final String MAY   = "may";
    public static final String SHDNT = "shouldnot";
    public static final String MUSNT = "mustnot";

    private final String[] _flags = new String[3];
    private boolean _valid = true;
}
