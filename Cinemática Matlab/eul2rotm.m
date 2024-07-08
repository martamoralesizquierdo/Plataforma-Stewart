function R = eul2rotm(eul)
    % eul: [yaw, pitch, roll]
    cy = cos(eul(1));
    sy = sin(eul(1));
    cp = cos(eul(2));
    sp = sin(eul(2));
    cr = cos(eul(3));
    sr = sin(eul(3));

    R = [cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr;
         sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr;
         -sp,     cp * sr,               cp * cr];
end
