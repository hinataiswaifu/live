#pragma once

#define MULTIPLAYER 1
#if MULTIPLAYER
#include "cocos/network/WebSocket.h"

#define selfPlayer 0
#define opponentPlayer 1
#define HOST "localhost:4200"
class MainScene;

class WebSocketClientDelegate : public cocos2d::network::WebSocket::Delegate {
private:
    MainScene *m_scene;

public:
    WebSocketClientDelegate(MainScene *m_scene);

    virtual void onOpen(cocos2d::network::WebSocket* ws) override;
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data) override;
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error) override;
    virtual void onClose(cocos2d::network::WebSocket* ws) override;
};

class NetworkManager {
private:
    MainScene* m_scene;
    cocos2d::network::WebSocket* m_socket;
public:
    NetworkManager(MainScene *m_scene);
    void update();
};
#endif
