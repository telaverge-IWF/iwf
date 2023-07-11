package com.intellinet.diameter.mag.util;

import com.intellinet.diameter.mag.node.AQualifier;


public class Qualifier {
    public static final int INFINITY = -1;

    public Qualifier() {
        _min = 0;
        _max = INFINITY;
    }

    public Qualifier(AQualifier node, int minOccurance) {
        if (node != null) {
            try {
                _min = Integer.parseInt(node.getMin().getText());
            } catch (Throwable t) {
                _min = minOccurance;
            }
            try {
                _max = Integer.parseInt(node.getMax().getText());
            } catch (Throwable t) {
                _max = INFINITY;
            }
        } else {
            _min = minOccurance;
            _max = Math.max(1, minOccurance);
        }
    }

    public int getMin() {
        return _min;
    }

    public int getMax() {
        return _max;
    }

    private int _min;
    private int _max;
}
