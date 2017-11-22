#pragma once

#define MULTIPLAYER 1
#if MULTIPLAYER
#include "cocos/network/WebSocket.h"

#define selfPlayer 0
#define opponentPlayer 1
#define HOST "localhost:4200"
class MainScene;

class WebSocketClientDelegate : public network::WebSocket::Delegate {
private:
    MainScene *m_scene;

public:
    WebSocketClientDelegate(MainScene *m_scene);

    virtual void onOpen(network::WebSocket* ws) override;
    virtual void onMessage(network::WebSocket* ws, const network::WebSocket::Data& data) override;
    virtual void onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) override;
    virtual void onClose(network::WebSocket* ws) override;
};

class NetworkManager {
private:
    MainScene* m_scene;
    network::WebSocket* m_socket;
public:
    NetworkManager(MainScene *m_scene);
    void update();
};
#endif
