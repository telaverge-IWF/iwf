/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TReq extends Token
{
    public TReq()
    {
        super.setText("REQ");
    }

    public TReq(int line, int pos)
    {
        super.setText("REQ");
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TReq(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTReq(this);
    }

    public void setText(String text)
    {
        throw new RuntimeException("Cannot change TReq text.");
    }
}
