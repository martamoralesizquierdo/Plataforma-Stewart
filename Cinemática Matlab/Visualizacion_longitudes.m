%% Visualización Longitudes stewart
 % x, y, z: posición de la plataforma
 % A, B, C: ángulos de la plataforma en radianes (roll, pitch, yaw)
 % b: radio de los puntos de anclaje en la base
 % p: radio de los puntos de anclaje en la plataforma
p = 23;
b= 23;

%% Ejemplo 1
E1 = stewart_inverse_kinematics(10,10,10,0,0,0,p,b)
%Gráficos
%Podemos representar un pequeño esquema de las longitudes de cada pata:
figure
%bar([n1,n2,n3,n4,n5,n6],0.4,'b')
bar(E1,0.4,'b')
xlabel Patas
ylabel 'Longitud de las patas'

%% Ejemplo 2
E2 = stewart_inverse_kinematics(0,0,0,2,4,0,p,b)
figure
bar(E2,0.4,'b')
xlabel Patas
ylabel 'Longitud de las patas'

%% Ejemplo 3
E3 = stewart_inverse_kinematics(1,4,5,2,2,0,p,b)
figure
bar(E3,0.4,'b')
xlabel Patas
ylabel 'Longitud de las patas'

%% Ejemplo 4
E4 = stewart_inverse_kinematics(-7,3,4,10,6,1,p,b)
figure
bar(E3,0.4,'b')
xlabel Patas
ylabel 'Longitud de las patas'


%% % Ejemplo de uso
r_base = 23; % Radio del hexágono de la base en cm
r_plat = 23; % Radio del hexágono de la plataforma en cm
height_plat = 30; % Altura de la plataforma en cm

[B, P] = define_anchor_points(r_base, r_plat, height_plat);
disp('Puntos de anclaje en la base (B):');
disp(B);
disp('Puntos de anclaje en la plataforma (P):');
disp(P);

% Definir la posición y orientación de la plataforma
x = 10;
y = 10;
z = 10; % La plataforma está a la altura de los actuadores desde la base
roll = 0;
pitch = 0;
yaw = 0;

% Calcular las longitudes de los actuadores
d = stewart_inverse_kinematics(x, y, z, roll, pitch, yaw, B, P);
disp('Longitudes de los actuadores:');
disp(d);
