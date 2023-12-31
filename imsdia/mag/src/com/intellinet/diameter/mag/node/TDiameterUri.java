/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TDiameterUri extends Token
{
    public TDiameterUri()
    {
        super.setText("DiamURI");
    }

    public TDiameterUri(int line, int pos)
    {
        super.setText("DiamURI");
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TDiameterUri(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTDiameterUri(this);
    }

    public void setText(String text)
    {
        throw new RuntimeException("Cannot change TDiameterUri text.");
    }
}
