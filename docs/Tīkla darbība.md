# Tīkla darbība #
Arseniuss

Sākuma ideja bija, ka _hosts_ sūta visiem savu uzģenerēto mapi un pārējie to attēlo. Bet, lai to nodrošinātu, ir visu laiku sājūta vismaz 16 KB ik pēc 1/4 sekundēm.
Šādi spēlēs veiktspēja strauji samazināsies un drīzāk ir jāpielieto cita spēles sinhronizācijas metode.

Veids, kuru izmanto spēļu industrijā, ir tāda, ka tiek sūtīti tikai nepieciešamie dati visiem lietotājiem. Un reizē tiek sinhronizēts spēles ātrums.

Spēle sākas ar to, ka lietotājiem tiek dota iespēja izvēlēties, kur ielikt savas pirmās četras šūnas. Kad abi lietotāji to ir izdarījuši sākas tālāko ģenerāciju cikls, kurā tiek padotas ziņas starp lietotāju clientiem.

Kad klients ir uzģenerējusi nākošo ģenerāciju, tad sūta otram klientam apstriprinājumu. Un gaida līdz atnāk apstriprinājums no otra klienta par tās pašas ģenerācijas uzģenerēšanu.

Ja lietotājs kādā ģenerācijā izveido jaunu šūnu, tad līdz ap apstriprinājumu tiek sūtītas arī jauno šūnu koordinātas.

Ik pēc kāda laika arī tiek sūtīta populācijas sinhronizācija, lai pārbaudītu, lai abiem klientie ģenerācijas ir identiskas.

Gadījuma, ka parādas sinhronizācijas kļūdas. Spēle tiek apstrādināta un spēles laukums tiek sinhronizēts.

Kad spēle ir beigusies, abi klienti otram nosūta statistikas datus, kas ir reģistrētā populācija ik pēc noteikta laika. Piemēram, ik pēc minūtes vai 30 sekundēm.

_Messages_:

MSG_ACK &lt;ģenerācijas numurs&gt; [&lt;lietotāja jauno šūnu skaits&gt; {&lt;x&gt; &lt;y&gt;}*]

MSG_POP &lt;ģenerācijas numurs&gt; &lt;pirmā spēlētāja populācija&gt; &lt;otrā spēlētāja populācija&gt;

MSG_SYNC &lt;ģenerācijas numurs&gt; &lt;spēles karte&gt;

MSG_STAT_GET &lt;skaits&gt; {&lt;ģeneraciju numuri vai laiki&gt;}*

MSG_STAT_REP &lt;skaits&gt; {&lt;ģeneraciju numuri vai laiki&gt; &lt;populācija&gt;}*




