namespace Steppers{
    constexpr int
        STEP1 = 2,
        STEP2 = 3,
        EN = 8, 
        DIR1 = 5,
        DIR2 = 6;
}
namespace Capteur{
    constexpr int    
        CapteurX = 9,
        CapteurY = 10;
}
namespace Actionneur{
    constexpr int 
        Servo_rot = 12,
        Servo_hauteur = 13,
        Pompe = 4,
        Vanne = 11, // Pin 11 gère les 2 pins z+/z-
        Pompe1B = 7;
}
