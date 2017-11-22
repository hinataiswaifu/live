#include "NetworkManager.h"

#if MULTIPLAYER
#include "MainScene.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/stream.hpp>

WebSocketClientDelegate::WebSocketClientDelegate(MainScene *m_scene): m_scene(m_scene) {}

void WebSocketClientDelegate::onOpen(network::WebSocket* ws) {}

void WebSocketClientDelegate::onMessage(network::WebSocket* ws, const network::WebSocket::Data& data) {
    CCLOG("onMessage");
    if( !m_scene->isStarted() ) {
        m_scene->startGame(data.bytes[0]);
        return;
    }
    boost::iostreams::stream<boost::iostreams::array_source> is(data.bytes, data.len);
    boost::archive::binary_iarchive ia(is);
    float x, y;
    Direction dir;
    ia >> x >> y >> dir;

    m_scene->getPlayer(opponentPlayer)->setPosition(Point(x, y), dir);
    m_scene->getPlayer(opponentPlayer)->setZOrder(-(m_scene->getPlayer(opponentPlayer)->getPosition().y - PLAYER_SPRITE_HEIGHT / 2));
}

void WebSocketClientDelegate::onError(network::WebSocket* ws, const network::WebSocket::ErrorCode& error) {}

void WebSocketClientDelegate::onClose(network::WebSocket* ws) { CC_SAFE_DELETE(ws); }

NetworkManager::NetworkManager(MainScene* m_scene): m_scene(m_scene) {
    m_socket = new network::WebSocket();
    m_socket->init(*new WebSocketClientDelegate(m_scene), HOST);
}

void NetworkManager::update() {
    char buf[1000];
    size_t bufSize = sizeof(buf);
    boost::iostreams::stream<boost::iostreams::array_sink> os(buf, bufSize);
    boost::archive::binary_oarchive oa(os);
    oa << m_scene->getPlayer(selfPlayer)->getPosition().x
       << m_scene->getPlayer(selfPlayer)->getPosition().y
       << m_scene->getPlayer(selfPlayer)->getOrientation();
    m_socket->send((unsigned char*) buf, bufSize);
}
#endif
