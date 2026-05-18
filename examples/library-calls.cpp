auto replyLeft = GetRepository().NewChannel(ChannelMode::Async, Type::List(Type::Int));
auto replyRight = GetRepository().NewChannel(ChannelMode::Async, Type::List(Type::Int));

GetRepository().RegisterReaction({replyLeft, replyRight}, {pivot, reply}, 3);