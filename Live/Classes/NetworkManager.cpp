#include "NetworkManager.h"

#if MULTIPLAYER
#include "MainScene.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/string.hpp>
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
    std::string sprite_name;
    ia >> x >> y >> dir;
    ia >> sprite_name;


    m_scene->getPlayer(opponentPlayer)->setPosition(Point(x, y), dir);
    m_scene->getPlayer(opponentPlayer)->setZOrder(-(m_scene->getPlayer(opponentPlayer)->getPosition().y - PLAYER_SPRITE_HEIGHT / 2));

    if (sprite_name.compare("x") == 0) {
        for (auto it : m_scene->getMapItems()) {
            if (m_scene->getPlayer(opponentPlayer)->distanceFrom(*it) < 20) {
                it->getSprite()->removeFromParent();
                m_scene->getHUD()->enqueueMessage("Other player picked up a " + it->getName());
                m_scene->getMapItems().erase(
                        std::remove(m_scene->getMapItems().begin(), m_scene->getMapItems().end(), it));
                break;  // Only allow one pick up at a time
            }
        }
    } else if (sprite_name.length() > 0) {
        std::string sprite_file;
        unsigned int health, weight;
        float scale;
        // then there is a dropped item
        ia >> sprite_file >> weight >> health >> scale;
        Food* food = new Food(sprite_file, weight, sprite_name);
        food->setHealthInc(health);
        food->setScale(scale);
        m_scene->addMapItem(food, Point(x,y));
    }
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
    Food* food = m_scene->getDroppedFood();
    oa << m_scene->getPlayer(selfPlayer)->getPosition().x
       << m_scene->getPlayer(selfPlayer)->getPosition().y
       << m_scene->getPlayer(selfPlayer)->getOrientation();

    if (food != nullptr) {
        oa << food->getName();
        if (food->getName().compare("x") != 0) {
           oa << food->getSpriteFile()
               << food->getWeight()
               << food->getHealthInc()
               << food->getScale();
        }
    } else {
        oa << std::string("");
    }

    m_socket->send((unsigned char*) buf, bufSize);
}
#endif
