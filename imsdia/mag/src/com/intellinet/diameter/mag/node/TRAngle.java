/* This file was generated by SableCC (http://www.sablecc.org/). */

package com.intellinet.diameter.mag.node;

import com.intellinet.diameter.mag.analysis.*;

public final class TRAngle extends Token
{
    public TRAngle()
    {
        super.setText(">");
    }

    public TRAngle(int line, int pos)
    {
        super.setText(">");
        setLine(line);
        setPos(pos);
    }

    public Object clone()
    {
      return new TRAngle(getLine(), getPos());
    }

    public void apply(Switch sw)
    {
        ((Analysis) sw).caseTRAngle(this);
    }

    public void setText(String text)
    {
        throw new RuntimeException("Cannot change TRAngle text.");
    }
}
