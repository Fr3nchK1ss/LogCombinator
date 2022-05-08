import QtQuick 2.0
import QtQuick.Particles

ParticleSystem {
    ImageParticle {
        anchors.fill: parent
        source: "qrc:///particleresources/fuzzydot.png"
        color: "green"
        greenVariation: 0.2
        opacity: 0.6
    }

    Emitter {
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        emitRate: 20
        lifeSpan: 5000

        velocity: PointDirection{ y: 30; yVariation: 0 }
        size: 10
        sizeVariation: 5
    }

}
