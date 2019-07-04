#define DEFN_OPERATION(NAME) \
    void op_##NAME();

DEFN_OPERATION(list);
DEFN_OPERATION(create);
DEFN_OPERATION(query);
DEFN_OPERATION(update);
DEFN_OPERATION(credit_transfer);
DEFN_OPERATION(credit_deposit);
DEFN_OPERATION(campus_deposit);
DEFN_OPERATION(consume);
DEFN_OPERATION(bind);
