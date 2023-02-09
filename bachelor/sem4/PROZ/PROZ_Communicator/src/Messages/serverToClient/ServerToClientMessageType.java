package Messages.serverToClient;

public enum ServerToClientMessageType {
    CONFIRM_LOGIN,
    REJECT_LOGIN,
    LOGOUT,
    USER_WANTS_TO_BE_YOUR_FRIEND,
    USER_ACCEPTED_YOUR_FRIEND_REQUEST,
    TEXT_MESSAGE_FROM_USER,
    TEXT_MESSAGE_FROM_GROUP,
    USER_IS_NOT_CONNECTED,
    GROUP_NAME_OCCUPIED,
    USER_ADDED_YOU_TO_GROUP,
    IMAGE,

}