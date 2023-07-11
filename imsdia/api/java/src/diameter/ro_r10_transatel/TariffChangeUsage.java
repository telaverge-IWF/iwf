package diameter.ro_r10_transatel;

import com.intellinet.diameter.*;


/**
 * The Tariff-Change-Usage AVP (AVP Code 452) is of type Enumerated and defines
 * whether units are used before or after a tariff change, or whether the units
 * straddled a tariff change during the reporting period. Omission of this AVP
 * means that no tariff change has occurred.
 * In addition, when present in answer messages as part of the Multiple-
 * Services-Credit-Control AVP, this AVP defines whether units are allocated to
 * be used before or after a tariff change event.
 * When the Tariff-Time-Change AVP is present, omission of this AVP in answer
 * messages means that the single quota mechanism applies.
 */
public class TariffChangeUsage extends com.intellinet.diameter.DerivedAVP<Integer> {
    public static enum Value {
        UNIT_BEFORE_TARIFF_CHANGE(0),
        UNIT_AFTER_TARIFF_CHANGE(1),
        UNIT_INDETERMINATE(2);

        public final int id;

        private Value(int id) { this.id = id; }
    };

    /**
     * Constructs a TariffChangeUsage with the given value.
     *
     * @param value - the value of the AVP
     */
    public TariffChangeUsage(Value value) {
        super(new com.intellinet.diameter.EnumeratedData(value.id));    }

    TariffChangeUsage(com.intellinet.diameter.EnumeratedData data) {
        super(data);
    }
}
