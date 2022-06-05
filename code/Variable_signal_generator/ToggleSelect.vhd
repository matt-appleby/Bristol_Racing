-- VHDL code for toggle select
-- If sel = 1, Y=A
--    sel = 0, Y=B

--Needs 2008 to compile, can't get to work in 2002 cause i'm bad at vhdl

Library IEEE;
USE IEEE.std_logic_1164.all;
use ieee.numeric_std.all;

entity toggle_select is 
   port(
        A : in std_logic_vector(3 downto 0);
        B : in std_logic_vector(3 downto 0);
        Y : out std_logic_vector(3 downto 0);
        sel : in std_logic
);
end toggle_select;


architecture Behavioral of toggle_select is  
signal A_buf : std_logic_vector(3 downto 0);
signal B_buf : std_logic_vector(3 downto 0);
signal Y_buf : std_logic_vector(3 downto 0);
begin  
 process(A,B,Y,sel)
 begin
    if(sel='1') then
        Y <= A;
    elsif(sel='0') then
        Y <= B;
    end if;
 end process;  
end Behavioral; 