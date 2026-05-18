class Reaction3: public Runnable {
public:
    Reaction3(Objects context)
    : pivot(ToInt(context[0]))
    , reply(ToChannel(context[1])) {}

    void operator()(Objects inputs) override {
        auto leftReply = ToList(inputs[0]);
        auto rightReply = ToList(inputs[1]);
        reply.Send(concat(left, pivot, right));
    }

    int64_t GetID() const noexcept override {
        return 3;
    }
private:
  Int pivot;
  Channel reply;
};