import cv2
import os
import numpy as np
from cv2 import aruco
import math

#définition des markers
dictionary = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
detector = aruco.ArucoDetector(dictionary)

#définition de la taille du marker en cm
MARKER_SIZE = 4

dist_coeffs = np.zeros((5, 1), dtype=np.float32)

# Coordonnées 3D du marker (carré)
half_size = MARKER_SIZE / 2
obj_points = np.array([
    [-half_size,  half_size, 0],
    [ half_size,  half_size, 0],
    [ half_size, -half_size, 0],
    [-half_size, -half_size, 0]
], dtype=np.float32)

# Dossier de sauvegarde
save_path = "photos"
os.makedirs(save_path, exist_ok=True)

#choisir la caméra
cap = cv2.VideoCapture(0)

#prendre en photo
ret, frame = cap.read()
filename = os.path.join(save_path, "photo.jpg")
cv2.imwrite(filename, frame)
print(f"Photo sauvegardée : {filename}")

#Applique à image le chemin de la photo prise
image = cv2.imread(r"C:\Users\maxim\Desktop\logiciel\ArUco detect\photos\photo.jpg")

# Convertir l'image en niveaux de gris
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Matrice de la caméra (pour la calibration)
h, w = gray.shape[:2]
focal_length = w  
camera_matrix = np.array([
    [468.52725179,   0.     ,    301.69032887],
    [  0.     ,    470.71372341, 250.25035561],
    [  0.      ,     0.      ,     1.        ]
], dtype=np.float32)

#détection des markers sur l'image avec les niveaux de gris
corners, ids, _ = detector.detectMarkers(gray)

def init_mk_5():
    """Initialise les coordonnées du marker 5 et son angle de rotation pour en faire un point d'origine"""
    if ids is not None:
        for i in range(len(ids)):
            if ids[i] == 5:
                img_points = corners[i][0]
                success, rvec, tvec = cv2.solvePnP(
                                obj_points,
                                img_points,
                                camera_matrix,
                                dist_coeffs
                            )
    if success:
        tvec[2][0] = 0
        R, _ = cv2.Rodrigues(rvec)
        angle_z = math.degrees(math.atan2(R[1,0], R[0,0]))
        return tvec, angle_z

#coordonnées par rapport au marker 5
positions = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
if ids is not None:
    tvec_marker_5, rvec_marker_5 = init_mk_5()
    
    print(tvec_marker_5)
    for i in range(len(ids)):
        img_points = corners[i][0]
        if ids[i] == 5:
            continue
        success, rvec, tvec = cv2.solvePnP(
                        obj_points,
                        img_points,
                        camera_matrix,
                        dist_coeffs
                    )
        if success:
            if ids[i] == 1:
                """ajoute à la liste les coordonnées et 
                l'angle de rotation du marker 1 par rapport au marker 5"""
                tvec[2][0] = 0
                tvec_mk = tvec - tvec_marker_5
                #tvec_mk[1][0] = - tvec_mk[1][0]
                #tvec_mk[0][0] = - tvec_mk[0][0]
                tvec_mk[0][0] =  35 - tvec_mk[0][0]
                tvec_mk[1][0] =  29 - tvec_mk[1][0]
                tvec_mk[2][0] = 0
                np.set_printoptions(legacy="1.25")
                positions[0] = tvec_mk[1][0]
                positions[1] = tvec_mk[0][0]
                R, _ = cv2.Rodrigues(rvec)
                angle_z = math.degrees(
                    math.atan2(R[1,0], R[0,0])
                )
                positions[2] = angle_z - rvec_marker_5
                print(f"Marker {ids[i]}:")
                print(angle_z-rvec_marker_5)
                print(tvec_mk)
                
            if ids[i] == 2:
                """ajoute à la liste les coordonnées et 
                l'angle de rotation du marker 2 par rapport au marker 5"""
                tvec[2][0] = 0
                tvec_mk = tvec - tvec_marker_5
                tvec_mk[1][0] = - tvec_mk[1][0] 
                tvec_mk[2][0] = 0
                np.set_printoptions(legacy="1.25")
                positions[3] = tvec_mk[0][0]
                positions[4] = tvec_mk[1][0]
                R, _ = cv2.Rodrigues(rvec)
                angle_z = math.degrees(
                    math.atan2(R[1,0], R[0,0])
                )
                positions[5] = angle_z - rvec_marker_5
                print(f"Marker {ids[i]}:")
                print(angle_z-rvec_marker_5)
                print(tvec_mk)
                
            if ids[i] == 3:
                """ajoute à la liste les coordonnées et 
                l'angle de rotation du marker 3 par rapport au marker 5"""
                tvec[2][0] = 0
                tvec_mk = tvec - tvec_marker_5
                tvec_mk[1][0] = - tvec_mk[1][0] 
                tvec_mk[2][0] = 0
                np.set_printoptions(legacy="1.25")
                positions[6] = tvec_mk[0][0]
                positions[7] = tvec_mk[1][0]
                R, _ = cv2.Rodrigues(rvec)
                angle_z = math.degrees(
                    math.atan2(R[1,0], R[0,0])
                )
                positions[8] = angle_z - rvec_marker_5
                print(f"Marker {ids[i]}:")
                print(angle_z-rvec_marker_5)
                print(tvec_mk)

            if ids[i] == 4:
                """ajoute à la liste les coordonnées et 
                l'angle de rotation du marker 4 par rapport au marker 5"""
                tvec[2][0] = 0
                tvec_mk = tvec - tvec_marker_5
                tvec_mk[1][0] = - tvec_mk[1][0] 
                tvec_mk[2][0] = 0
                np.set_printoptions(legacy="1.25")
                positions[9] = tvec_mk[0][0]
                positions[10] = tvec_mk[1][0]
                R, _ = cv2.Rodrigues(rvec)
                angle_z = math.degrees(
                    math.atan2(R[1,0], R[0,0])
                )
                positions[11] = angle_z - rvec_marker_5
                print(f"Marker {ids[i]}:")
                print(angle_z-rvec_marker_5)
                print(tvec_mk)
    print(f"Positions: {positions}")

#affiche l'image modifiée
cv2.imshow("Image", gray)
cv2.waitKey(0)

#envoie le tableau avec les coordonnées


#libère la caméra et ferme les fenêtres
cap.release()
cv2.destroyAllWindows()