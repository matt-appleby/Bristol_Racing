-- VHDL script to test the ToggleSelect script
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
ENTITY toggle_select_tb IS
END toggle_select_tb;

architecture behavior of toggle_select_tb is
    component toggle_select
    port(
        A : in std_logic_vector(3 downto 0);
        B : in std_logic_vector(3 downto 0);
        Y : out std_logic_vector(3 downto 0);
        sel : in std_logic
    );
    end component;

    --Inputs
    signal A : std_logic_vector(3 downto 0); -- :='1111';
    signal B : std_logic_vector(3 downto 0); -- :='0000';
    --Outputs
    signal Y : std_logic_vector(3 downto 0) :="0000";
    signal sel : std_logic; -- := '0';
    begin
        uut: toggle_select port map (
            A => A,
            B => B,
            Y => Y,
            sel => sel
        );

        stim_proc: process
        begin
            sel <= '0';
            A <= "1111";
            B <= "0000";
            wait for 10 ns;
            sel <= '1';
            A <= "1111";
            B <= "0000";
            wait for 10 ns;
            sel <= '0';
            A <= "1111";
            B <= "0000";
            wait for 10 ns;
            sel <= '0';
            A <= "1111";
            B <= "0000";
            wait for 10 ns;
            sel <= '1';
            A <= "1111";
            B <= "0000";
            wait for 10 ns;
            sel <= '1';
            A <= "1111";
            B <= "0000";
            wait for 10 ns;
            sel <= '0';
            A <= "1111";
            B <= "0000";
            wait for 10 ns;
            wait;
        end process;
    end;