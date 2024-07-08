function [B, P] = define_anchor_points(r_base, r_plat, height_plat)
    % r_base: radio del hexágono de la base
    % r_plat: radio del hexágono de la plataforma
    % height_plat: altura de la plataforma (distancia entre base y plataforma)

    theta_base = 2 * pi / 6 * (0:5); % Ángulos para los puntos del hexágono de la base
    theta_plat = 2 * pi / 6 * (0:5) + pi/6; % Ángulos para los puntos del hexágono de la plataforma (contrapeados)

    % Coordenadas de los puntos de anclaje en la base
    B = [r_base * cos(theta_base); 
         r_base * sin(theta_base); 
         zeros(1, 6)]; % La base está en el plano z = 0
    
    % Coordenadas de los puntos de anclaje en la plataforma
    P = [r_plat * cos(theta_plat); 
         r_plat * sin(theta_plat); 
         height_plat * ones(1, 6)]; % La plataforma está en z = height_plat
end

