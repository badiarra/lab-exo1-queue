#include "HC_SR04.h"

// CONSTRUCTEUR

HC_SR04::HC_SR04(int trig, int echo)
{
    trigPin = trig;
    echoPin = echo;
}

// INITIALISATION

void HC_SR04::init()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}


float HC_SR04::getDistance()
{
    // Déclenchement

    digitalWrite(trigPin, LOW);

    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);

    delayMicroseconds(10);

    digitalWrite(trigPin,LOW);


    // Lecture du temps de retour

    long duree = pulseIn(echoPin, HIGH, 30000);

    // Pas de mesure valide

    if (duree <= 0)
    {
        return -1.0;
    }

    // Calcul de la distance en cm

    float distance = duree * 0.0343 / 2.0;

    return distance;
}

void HC_SR04::vTaskSensor(void *pvParam){

    HC_SR04 *sensor = static_cast<HC_SR04 *>(pvParam);

    float distanceMeasured;

    while (true) {
         distanceMeasured = sensor->getDistance();
        if(sensor->queue != nullptr){
            xQueueSend(sensor->queue, &distanceMeasured, 0); //Accessible ici car vTaskSensor reste membre de la classe
        }
    vTaskDelay(pdMS_TO_TICKS(200));
  }
}

void HC_SR04::start(){
    xTaskCreate(vTaskSensor,"Mesures",2048, this,2,&handle);
}
 
void HC_SR04::setQueue(QueueHandle_t dataQueue){
    queue  = dataQueue;
}

void HC_SR04::stop(){
    
    if(handle != nullptr){
        vTaskDelete(handle);
    }
   
 }