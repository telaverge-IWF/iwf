/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import java.util.*;
import com.intellinet.diameter.mag.analysis.*;

public final class APrivateAvpFlag extends PAvpFlag
{

    public APrivateAvpFlag()
    {
    }
    public Object clone()
    {
        return new APrivateAvpFlag();
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseAPrivateAvpFlag(this);
    }

    public String toString()
    {
        return "";
    }

    void removeChild(Node child)
    {
    }

    void replaceChild(Node oldChild, Node newChild)
    {
    }
}
