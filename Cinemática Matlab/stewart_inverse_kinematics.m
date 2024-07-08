function d = stewart_inverse_kinematics(x, y, z, A, B, C, b, p)
    % Calcular los ángulos de los actuadores
    theta = 2 * pi / 6 * (0:5);

    % Calcular las longitudes de los actuadores
    d = zeros(1, 6);
    for i = 1:6
        alpha = A + p / b * (cos(B) * sin(theta(i)) - sin(B) * cos(theta(i)) * cos(C));
        beta = B + p / b * cos(theta(i)) * sin(C);
        gamma = C + p / b * (sin(B) * sin(theta(i)) + cos(B) * cos(theta(i)) * cos(C));

        xi = x + b * cos(alpha) * sin(beta);
        yi = y + b * sin(alpha) * sin(beta);
        zi = z + b * cos(beta);

        dx = xi - p * cos(theta(i));
        dy = yi - p * sin(theta(i));
        dz = zi;

        d(i) = sqrt(dx^2 + dy^2 + dz^2);
        
    end
end
