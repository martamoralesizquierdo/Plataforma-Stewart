function d = stewart_inverse_kinematics1(x, y, z, roll, pitch, yaw, B, P)
    % x, y, z: posición de la plataforma
    % roll, pitch, yaw: ángulos de la plataforma en radianes (A, B, C)
    % B: posiciones de los puntos de anclaje en la base (3x6 matriz)
    % P: posiciones de los puntos de anclaje en la plataforma (3x6 matriz)

    % Matriz de rotación de la plataforma
    R = eul2rotm([yaw, pitch, roll]);

    % Posición y orientación de la plataforma
    pos = [x; y; z];

    % Calcular las posiciones transformadas de los puntos de anclaje de la plataforma
    plat_positions = R * P + pos;

    % Calcular las longitudes de los actuadores
    d = zeros(1, 6);
    for i = 1:6
        dx = plat_positions(1, i) - B(1, i);
        dy = plat_positions(2, i) - B(2, i);
        dz = plat_positions(3, i) - B(3, i);

        d(i) = sqrt(dx^2 + dy^2 + dz^2);
    end
end
