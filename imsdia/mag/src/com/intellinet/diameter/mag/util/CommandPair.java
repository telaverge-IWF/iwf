package com.intellinet.diameter.mag.util;

import com.intellinet.diameter.mag.node.*;


public class CommandPair {
    public CommandPair(String name, String code, TInteger appId, TPxy pbit ) {
        this.name = name;
        this.appId = appId;
        this.proxyable = pbit != null;
        int c = 0;
        try {
            c = Integer.valueOf(code);
        } catch (Exception x) {
            System.err.println("Invalid command code " + code);
        }
        this.code = c;
    }

    public final String name;
    public final int code;
    public final TInteger appId;
    public final boolean proxyable;
    public ACommandDefinition req;
    public ACommandDefinition res;
}
