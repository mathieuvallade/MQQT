cmake_minimum_required(VERSION 3.5)

project(my_project)

# Ajoutez l'emplacement où la bibliothèque Paho MQTT est installée
find_package(PahoMqttCpp REQUIRED)

# Créer l'exécutable pour votre code C++
add_executable(my_app main.cpp)

# Lier votre code avec la bibliothèque Paho MQTT
target_link_libraries(my_app PahoMqttCpp::paho-mqttpp3)

# Inclure les fichiers d'en-tête pour la bibliothèque Paho MQTT
target_include_directories(my_app PRIVATE ${PAHO_MQTT_INCLUDE_DIRS})